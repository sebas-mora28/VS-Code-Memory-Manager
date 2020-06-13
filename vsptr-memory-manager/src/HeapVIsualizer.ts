/**
 * 
 * This class generate a WebView to visualize the heap visualizer
 */

import * as path from 'path';
import * as vscode from 'vscode'
import * as fs from 'fs'


export class HeapVisualizer {

	/**
	 * Track the currently panel. Only allow a single panel to exist at a time.
	 */
    public static currentPanel: HeapVisualizer | undefined;


	public static readonly viewType = 'extension';

	private readonly _panel: vscode.WebviewPanel;
	private readonly _extensionPath: string;
	private _disposables: vscode.Disposable[] = [];

	public static createOrShow(extensionPath: string) {
		const column = vscode.window.activeTextEditor
			? vscode.window.activeTextEditor.viewColumn
			: undefined;

		// If we already have a panel, show it.
		if (HeapVisualizer.currentPanel) {
			HeapVisualizer.currentPanel._panel.reveal(column);
			return;
		}

		// Otherwise, create a new panel.
		const panel = vscode.window.createWebviewPanel(
			HeapVisualizer.viewType,
			'Heap Visualizer',
			 vscode.ViewColumn.Beside,
			{
				// Enable javascript in the webview
				enableScripts: true,

				// And restrict the webview to only loading content from our extension's `media` directory.
				localResourceRoots: [vscode.Uri.file(path.join(extensionPath, 'src/view'))]
			}
		);

		HeapVisualizer.currentPanel = new HeapVisualizer(panel, extensionPath);
	}

	public static revive(panel: vscode.WebviewPanel, extensionPath: string) {
		HeapVisualizer.currentPanel = new HeapVisualizer(panel, extensionPath);
	}

	private constructor(panel: vscode.WebviewPanel, extensionPath: string) {
		this._panel = panel;
		this._extensionPath = extensionPath;
	 

		// Set the webview's initial html content



		setInterval(()=>{
			if(fs.existsSync(path.join(vscode.workspace.rootPath, 'lib/vsptr.json')) ||  fs.existsSync(path.join(this._extensionPath, 'src/vsptrRemote.json')) ){
				this._update();
			}else{
				console.log("No hay contenido");
			}
		}, 3000);

	

		

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
		HeapVisualizer.currentPanel = undefined;

		// Clean up our resources
		this._panel.dispose();

		while (this._disposables.length) {
			const x = this._disposables.pop();
			if (x) {
				x.dispose();
			}
		}
	}




	private getHeapTable(jsonFile : any) {
		const table = jsonFile.VSPtr.reduce((acc : any, data : any) => {
			return `
			${acc}
			<tr>
				<td>${data.id}</td>
				<td>${data.addr}</td>
				<td>${data.refcount}</td>
				<td>${data.value}</td>
				<td>${data.type}</td>
			</tr>
		`;
	}, '');

	return table; 
		
	}

	private getEmptyTable() {
		return `
		<tr>
				<td>No hay datos que mostrar</td>
			</tr>`
		
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



		
		const style = vscode.Uri.file(path.join(this._extensionPath, 'src', 'view', 'styleHeap.css'));
		const UriStyle = webview.asWebviewUri(style);


		
		let heap_local;
		if(fs.existsSync(path.join(vscode.workspace.rootPath, 'lib/vsptr.json'))){
			let jsonFile = JSON.parse(fs.readFileSync(path.join(vscode.workspace.rootPath, 'lib/vsptr.json'), 'utf8'));
			heap_local = this.getHeapTable(jsonFile);
		

		}else{
			heap_local =  this.getEmptyTable();
		}



	

		let heap_remote;
		//<link rel="stylesheet" type="text/css" href="${UriStyle}">
		if(fs.existsSync(path.join(this._extensionPath, 'src/vsptrRemote.json'))){
			let jsonFileServer = JSON.parse(fs.readFileSync(path.join(this._extensionPath, 'src/vsptrRemote.json'), 'utf8'));
			heap_remote = this.getHeapTable(jsonFileServer);
	

		}else{
			heap_remote =  this.getEmptyTable();
		}

		let renderedHtlm = `<!DOCTYPE html>
            <html lang="en">
            <head>
				<meta charset="UTF-8">



				<style>

					table {
  					  	border-radius: 5px;
    					font-size: 12px;
    					font-weight: normal;
    					border: none;
    					border-collapse: collapse;
    					width: 100%;
    					max-width: 100%;
    					white-space: nowrap;
    					background-color: white;
  
					}


					td, th {
    					text-align: center;
    					padding: 8px;
					}

					td {
    					border-right: 1px solid #f8f8f8;
    					font-size: 12px;
    					text-shadow: black;
    					color: black;
    					text-align: center;
					}

					th {
  				  		color: #ffffff;
   						background: #4FC3A1;
					}

					tr:nth-child(even) {
    					background: #F8F8F8;
					}

					th:nth-child(odd) {
    					color: #ffffff;
   						 background: #324960;
					}



				</style> 

		
	
                <!--
                Use a content security policy to only allow loading images from https or from our extension directory,
                and only allow scripts that have a specific nonce.
                -->
                
				
				<meta name="viewport" content="width=device-width, initial-scale=1.0">

                <title>VSCode Heap Visualizer</title>
			</head>
					<body>
						<div class="container">
							<div class="table-responsive" style="overflow-x:auto;">
									<h1>Heap Visualizer Local</h1>
										<br />

										<table class="table-heap-local" id="vsptr_table">
											<tr>
												<th>id</th>
												<th>addr</th>
												<th>refCount</th>
												<th>value</th>
												<th>type</th>
											</tr>
											${ heap_local }
										</table> 

							</div>			
							
							
							
							<div class="table-heap-remote">
							<h1 id="title_heap_remote"> Heap Visualizer Remote </h1>
								<br />

								<table class="table-heap-remote" id="vsptr_remote_table">
									<tr>
										<th>id</th>
										<th>addr</th>
										<th>refCount</th>
										<th>value</th>
										<th>type</th>
									</tr>
									${ heap_remote }
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

