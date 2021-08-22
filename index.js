const {
  readFilePaths,
  writeFilePaths,
  clear,
  saveImageAsJpegSync,
  saveImageAsPngSync,
  putImageSync,
} = require('bindings')();

module.exports = {
  readFilePaths,
  writeFilePaths,
  clear,
  saveImageAsJpegSync,
  saveImageAsPngSync,
  putImageSync,
};
