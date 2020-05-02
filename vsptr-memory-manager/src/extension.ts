// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
import * as vscode from 'vscode';
import * as fs from 'fs'; 
import * as path from 'path';
import * as graph from './data.json';




const panel = vscode.window.createWebviewPanel('memoryManager', 'REMOTE GARBAGE COLLECTOR', vscode.ViewColumn.Beside, {

	enableScripts: true,
	localResourceRoots: [vscode.Uri.file(path.join('/home/david/HACKERPLACE/VS-Code-Memory-Manager/vsptr-memory-manager/', 'src/view'))]
});

// this method is called when your extension is activated
// your extension is activated the very first time the command is executed

export function activate(context: vscode.ExtensionContext) {

	// Use the console to output diagnostic information (console.log) and errors (console.error)
	// This line of code will only be executed once when your extension is activated
	console.log('Congratulations, your extension "vsptr-memory-manager" is now active!');

	context.subscriptions.push(
		vscode.commands.registerCommand('vscodeHeap.start', () => {
			ExtensionWebViewPanel.createOrShow(context.extensionPath);
		})
	);

	if (vscode.window.registerWebviewPanelSerializer) {
		// Make sure we register a serializer in activation event
		vscode.window.registerWebviewPanelSerializer(ExtensionWebViewPanel.viewType, {
			async deserializeWebviewPanel(webviewPanel: vscode.WebviewPanel, state: any) {
				console.log(`Got state: ${state}`);
				ExtensionWebViewPanel.revive(webviewPanel, context.extensionPath);
			}
		});
	}

	// The command has been defined in the package.json file
	// Now provide the implementation of the command with registerCommand
	// The commandId parameter must match the command field in package.json
	let disposable = vscode.commands.registerCommand('extension.vsptrMemoryManager', () => {
		// The code you place here will be executed every time your command is executed

		// Display a message box to the user
		vscode.window.showInformationMessage('VSPtr Memory Manager');


		//Add WebView content from index.html
		updateWebView();
		
	});

	context.subscriptions.push(disposable);
}


function updateWebView(){
	fs.readFile(path.join('/home/david/HACKERPLACE/VS-Code-Memory-Manager/vsptr-memory-manager/','/src/view', 'index.html'), (err, data)=>{
		if(err){
			console.log(err);
		}
		panel.webview.html = data.toString();  
	});

}

class ExtensionWebViewPanel {
	/**
	 * Track the currently panel. Only allow a single panel to exist at a time.
	 */
	public static currentPanel: ExtensionWebViewPanel | undefined;

	public static readonly viewType = 'extension';

	private readonly _panel: vscode.WebviewPanel;
	private readonly _extensionPath: string;
	private _disposables: vscode.Disposable[] = [];

	public static createOrShow(extensionPath: string) {
		const column = vscode.window.activeTextEditor
			? vscode.window.activeTextEditor.viewColumn
			: undefined;

		// If we already have a panel, show it.
		if (ExtensionWebViewPanel.currentPanel) {
			ExtensionWebViewPanel.currentPanel._panel.reveal(column);
			return;
		}

		// Otherwise, create a new panel.
		const panel = vscode.window.createWebviewPanel(
			ExtensionWebViewPanel.viewType,
			'Extension',
			column || vscode.ViewColumn.One,
			{
				// Enable javascript in the webview
				enableScripts: true,

				// And restrict the webview to only loading content from our extension's `media` directory.
				localResourceRoots: [vscode.Uri.file(path.join(extensionPath, 'media'))]
			}
		);

		ExtensionWebViewPanel.currentPanel = new ExtensionWebViewPanel(panel, extensionPath);
	}

	public static revive(panel: vscode.WebviewPanel, extensionPath: string) {
		ExtensionWebViewPanel.currentPanel = new ExtensionWebViewPanel(panel, extensionPath);
	}

	private constructor(panel: vscode.WebviewPanel, extensionPath: string) {
		this._panel = panel;
		this._extensionPath = extensionPath;

		// Set the webview's initial html content
		this._update();

		// Listen for when the panel is disposed
		// This happens when the user closes the panel or when the panel is closed programatically
		this._panel.onDidDispose(() => this.dispose(), null, this._disposables);

		// Update the content based on view changes
		this._panel.onDidChangeViewState(
			e => {
				if (this._panel.visible) {
					this._update();
				}
			},
			null,
			this._disposables
		);

		// Handle messages from the webview
		this._panel.webview.onDidReceiveMessage(
			message => {
				switch (message.command) {
					case 'alert':
						vscode.window.showErrorMessage(message.text);
						return;
				}
			},
			null,
			this._disposables
		);
	}

	public dispose() {
		ExtensionWebViewPanel.currentPanel = undefined;

		// Clean up our resources
		this._panel.dispose();

		while (this._disposables.length) {
			const x = this._disposables.pop();
			if (x) {
				x.dispose();
			}
		}
	}

	private _update() {
		const webview = this._panel.webview;

		// Local path to main script run in the webview
		const scriptPathOnDisk = vscode.Uri.file(
			path.join(this._extensionPath, 'media', 'main.js')
		);

		// And the uri we use to load this script in the webview
		const scriptUri = webview.asWebviewUri(scriptPathOnDisk);

		// Use a nonce to whitelist which scripts can be run
		const nonce = getNonce();

		const tableHtml = graph.VSPtr.reduce((acc, data) => {
			return `
				${acc}
				<tr>
					<td>${data.id}</td>
					<td>${data.addr}</td>
					<td>${data.refCount}</td>
					<td>${data.type}</td>
				</tr>
			`;
		}, '');

		const renderedHtlm = `<!DOCTYPE html>
            <html lang="en">
            <head>
				<meta charset="UTF-8">
				
				<style>
				table, th, td {
					border: 1px solid white;
				}
				</style>

                <!--
                Use a content security policy to only allow loading images from https or from our extension directory,
                and only allow scripts that have a specific nonce.
                -->
                <meta http-equiv="Content-Security-Policy" content="default-src 'none'; img-src ${webview.cspSource} https:; script-src 'nonce-${nonce}';">

                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <title>VSCode Heap Visualizer</title>
            </head>
						<body>
						<div class="container">
							<div class="table-responsive">
									<h1>Heap Visualizer</h1>
										<br />

										<table class="table table-bordered table-striped" id="vsptr_table">
											<tr>
												<th>id</th>
												<th>addr</th>
												<th>refCount</th>
												<th>type</th>
											</tr>
											${ tableHtml }
										</table>
									</div>
								</div>
                <script nonce="${nonce}" src="${scriptUri}"></script>
            </body>
						</html>`;

		
		
		this._panel.webview.html = renderedHtlm;
	}
}

function getNonce() {
	let text = '';
	const possible = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
	for (let i = 0; i < 32; i++) {
		text += possible.charAt(Math.floor(Math.random() * possible.length));
	}
	return text;
}