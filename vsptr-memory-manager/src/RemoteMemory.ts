/**
 * 
 * This class generate a WebView to visualize the heap visualizer
 */

import * as path from 'path';
import * as vscode from 'vscode';
import * as fs from 'fs';


export class RemoteMemory {

	/**
	 * Track the currently panel. Only allow a single panel to exist at a time.
	 */
    public static currentPanel: RemoteMemory | undefined;


	public static readonly viewType = 'extension';

	private readonly _panel: vscode.WebviewPanel;
	private readonly _extensionPath: string;
	private _disposables: vscode.Disposable[] = [];

	public static createOrShow(extensionPath: string) {
		const column = vscode.window.activeTextEditor
			? vscode.window.activeTextEditor.viewColumn
			: undefined;

		// If we already have a panel, show it.
		if (RemoteMemory.currentPanel) {
			RemoteMemory.currentPanel._panel.reveal(column);
			return;
		}

		// Otherwise, create a new panel.
		const panel = vscode.window.createWebviewPanel(
			RemoteMemory.viewType,
			'RemoteMemory',
			vscode.ViewColumn.Beside,
			{
				// Enable javascript in the webview
                enableScripts: true,
				// And restrict the webview to only loading content from our extension's `media` directory.
				localResourceRoots: [vscode.Uri.file(path.join(extensionPath,'src/view'))]
			}

		);

	        RemoteMemory.currentPanel = new RemoteMemory(panel, extensionPath);
	}

	public static revive(panel: vscode.WebviewPanel, extensionPath: string) {
		RemoteMemory.currentPanel = new RemoteMemory(panel, extensionPath);
	}

	private constructor(panel: vscode.WebviewPanel, extensionPath: string) {
		this._panel = panel;
		this._extensionPath = extensionPath;
	 

		// Set the webview's initial html content



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
				this.createConnectionInfo(message._PORT, message._IPADDRESS, message._PASSWORD);
			},
			null,
			this._disposables
		);
    }
    

    private createConnectionInfo(PORT : string, IpAdress : string, password : string) {


        const connectionInfo = {
            ConnectionInfo :
            {
                "PORT": parseInt(PORT),
                "IpAddress" : IpAdress,
                "password" : password
            }
        }

        const _path = path.join(vscode.workspace.rootPath, 'lib', 'connectionData.json');
        const connectionInfoConvertedToString = JSON.stringify(connectionInfo);
        fs.writeFileSync(_path, connectionInfoConvertedToString); 
        
    }


	public dispose() {
		RemoteMemory.currentPanel = undefined;

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
        


        const style = vscode.Uri.file(
            path.join(this._extensionPath,'src', 'view','styleRemoteMemory.css')
        );


        const UriStyle = this._panel.webview.asWebviewUri(style);


    



	

		let renderedHtlm = `<!DOCTYPE html>
		<html>
			<body>


				<style> 



					#title {
    				color: white;
    				position: absolute;
    				left: 100px;
					}

					#default_port {
    					position: absolute;
    					left: 50px;
    					top: 90px;
    					font-family: Arial, Helvetica, sans-serif;
    					font-weight: bold;
    					font-size: 20px;
    					color:white;
					}

					#default_ip {
    					position: absolute;
    					left: 53px;
    					top: 140px;
    					font-family: Arial, Helvetica, sans-serif;
    					font-size: 20px;
    					font-weight: bold;
    					color : white
					}

					#defualt_password {
    					position: absolute;
    					left: 53px;
    					top: 190px;
    					font-family: Arial, Helvetica, sans-serif;
    					font-size: 20px;
    					font-weight: bold;
    					color : white


					}

					#connection{
    					position: absolute;
    					left: 53px;
    					top: 530px;
    					width: 135px;
    					height: 40px;
    					font-weight: bold;
    					font-family: Cambria, Cochin, Georgia, Times, 'Times New Roman', serif;
    					font-size: 20px;
    					background-color: rgb(41, 179, 23);
					}


					input{
    					font-size: 25px;
    					font-family: Cambria, Cochin, Georgia, Times, 'Times New Roman', serif;
    					font-weight: bold;
   						width: 240px;
    					height: 35px;
					}


					#ipAddress{
    					position: absolute;
    					left: 50px;
    					top: 270px;
 

					}

					#labelIpAddress{
    					position: absolute;
    					left: 53px;
    					top: 230px;
    					font-size: 30px;
    					font-family: Cambria, Cochin, Georgia, Times, 'Times New Roman', serif;
    					font-weight: bold;
					}


					#password{
  						position: absolute;
   						left: 53px;
    					top: 470px;

					}

					#labelPassword{
  						position: absolute;
  						left: 53px;
    					top: 430px;
    					font-size: 30px;
    					font-weight: bold;
    					font-family: Cambria, Cochin, Georgia, Times, 'Times New Roman', serif;
						}


					#port{
    					position: absolute;
    					left: 50px;
    					top:370px;

    
					}

					#labelPort{
    					position: absolute;
    					left: 53px;
    					top: 330px;
    					font-family: Cambria, Cochin, Georgia, Times, 'Times New Roman', serif;
    					font-size: 30px;
    					font-weight: bold;
					}


				</style>
		
				<head>
                    <script type="text/javascript" src='./view/clientInformation.ts'> </script>
                    <meta name="viewport" content="width=device-width, initial-scale=1.0">
                    
					<title >REMOTE GARBAGE COLLECTOR</title>
				</head>
		
				<h1 id="title"> REMOTE MEMORY </h1>
		
				<button id='connection' type="button" onclick="initClient()" >
					Connection
				</button>


				<p1 id="default_port"> Default PORT : 54000 </p1>
				<p1 id="default_ip" > Default Ip Address : 127.0.0.1</p1>
				<p1 id="defualt_password"> Default Password : GCSERVER</p1>
			
				<form>
		
					<label for="ipAddress" id="labelIpAddress"> Ip Address</label><br>
					<input type="text" id="ipAddress" name="ipAddress" ><br>
		
		
					<label for="password" id="labelPassword"> Password</label><br>
					<input type="password" id="password" name="password" pattern=".{6,}"><br>
		
		
					<label for="port" id="labelPort"> Port</label><br>
					<input type="text" id="port" name="port" ><br>
		
		
	
				</form>
			
			
				<label id="name"></label>
			
			
				<script type="text/javascript">

					const vscode = acquireVsCodeApi();

					function initClient(){

						const PORT = document.getElementById("port").value;
						const IpAdress = document.getElementById("ipAddress").value;
						const PASSWORD  = document.getElementById("password").value;

						vscode.postMessage({
							_PORT : PORT,
							_IPADDRESS : IpAdress,
							_PASSWORD : PASSWORD
						});	

					}
					
				
				</script>
		
				<script>
					const styleSrc = vscode.Uri.file()
                </script>
                

                <script nonce="${nonce}" src="${scriptUri}"></script>
		
            </body>
            
		</html>`

		
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

