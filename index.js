const {promisify} = require('util');
const {
  readFilePaths,
  writeFilePaths,
  clear,
  saveImageAsJpegSync,
  saveImageAsJpegAsync,
  saveImageAsPngSync,
  saveImageAsPngAsync,
  putImageSync,
  putImageAsync,
} = require('bindings')();

module.exports = {
  readFilePaths,
  writeFilePaths,
  clear,
  saveImageAsJpeg: promisify(saveImageAsJpegAsync),
  saveImageAsJpegSync,
  saveImageAsPng: promisify(saveImageAsPngAsync),
  saveImageAsPngSync,
  putImageSync,
  putImage: promisify(putImageAsync),
};
