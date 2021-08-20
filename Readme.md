# electron-clipboard-ex

A node.js native addon designed to use with [electron](https://www.electronjs.org/) to extend its clipboard features.
Please refer to [electron tutorial](https://electronjs.org/docs/tutorial/using-native-node-modules) for usage in electron.

## Example

Read file paths copied from macOS Finder or Windows explorer:

```javascript
const clipboardEx = require('electron-clipboard-ex');
const filePaths = clipboardEx.readFilePaths();
```

Write file paths to clipboard:

```javascript
const clipboardEx = require('electron-clipboard-ex');
clipboardEx.writeFilePaths(filePaths);
```

## Operating system support
This library supports Windows and macOS. Linux is currently not supported, feel free to open a pull request if you need it.
