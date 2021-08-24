# electron-clipboard-ex

A node.js native addon designed to use with [electron](https://www.electronjs.org/) to extend its clipboard features.
Please refer to [electron tutorial](https://electronjs.org/docs/tutorial/using-native-node-modules) for usage in electron.

![Travis](https://app.travis-ci.com/kenan2002/electron-clipboard-ex.svg?token=zab8ueZodq3Wkp6NTq2P&branch=master)
[![npm version](https://badge.fury.io/js/electron-clipboard-ex.svg)](https://badge.fury.io/js/electron-clipboard-ex)

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

Clear clipboard:
```javascript
const clipboardEx = require('electron-clipboard-ex');
clipboardEx.clear();
```

Save clipboard image as jpeg:
```javascript
const clipboardEx = require('electron-clipboard-ex');
// sync
clipboardEx.saveImageAsJpegSync(targetPath, compressFactor);
// async
await clipboardEx.saveImageAsJpeg(targetPath, compressFactor);
```

Save clipboard image as png:
```javascript
const clipboardEx = require('electron-clipboard-ex');
// sync
clipboardEx.saveImageAsPngSync(targetPath);
// async
await clipboardEx.saveImageAsPng(targetPath);
```

Put image into clipboard:
```javascript
const clipboardEx = require('electron-clipboard-ex');
// sync
clipboardEx.putImageSync(imagePath);
// async
await clipboardEx.putImage(imagePath);
```

## Operating system support
This library supports Windows and macOS. Linux is currently not supported, feel free to open a pull request if you need it.
