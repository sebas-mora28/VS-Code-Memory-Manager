// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
import * as vscode from 'vscode';
import * as fs from 'fs'; 
import * as path from 'path';	


const panel = vscode.window.createWebviewPanel('memoryManager', 'REMOTE GARBAGE COLLECTOR', vscode.ViewColumn.Beside, {

	enableScripts: true,
	localResourceRoots: [vscode.Uri.file(path.join('/home/sebasmora/Documents/TEC/Semestre III/Datos II/VS-Code-Memory-Manager/vsptr-memory-manager/', 'src/view'))]
})




// this method is called when your extension is activated
// your extension is activated the very first time the command is executed
export function activate(context: vscode.ExtensionContext) {

	// Use the console to output diagnostic information (console.log) and errors (console.error)
	// This line of code will only be executed once when your extension is activated
	console.log('Congratulations, your extension "vsptr-memory-manager" is now active!');

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

// this method is called when your extension is deactivated
export function deactivate() {}


function updateWebView(){
	fs.readFile(path.join('/home/sebasmora/Documents/TEC/Semestre III/Datos II/VS-Code-Memory-Manager/vsptr-memory-manager/','/src/view', 'index.html'), (err, data)=>{
		if(err){
			console.log(err);
		}
		panel.webview.html = data.toString();  
	})

}