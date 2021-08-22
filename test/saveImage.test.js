const path = require('path');
const fs = require('fs-extra');
const {clear, saveImageAsJpegSync, saveImageAsPngSync, putImageSync} = require('..');

const tempPath = path.resolve(__dirname, '../temp');
const jpegPath = path.resolve(tempPath, 'out.jpeg');
const pngPath = path.resolve(tempPath, 'out.png');
const sourceImage = path.resolve(__dirname, 'data/image.png');

beforeEach(() => {
  fs.removeSync(tempPath);
  fs.ensureDirSync(tempPath);
  clear();
});

afterEach(() => {
  fs.removeSync(tempPath);
  clear();
});

test('save jpeg -- normal', () => {
  expect(putImageSync(sourceImage)).toBe(true);
  const result = saveImageAsJpegSync(jpegPath, 1.0);
  expect(result).toBe(true);
  expect(fs.pathExistsSync(jpegPath)).toBe(true);
});

test('save png -- normal', () => {
  expect(putImageSync(sourceImage)).toBe(true);
  const result = saveImageAsPngSync(pngPath);
  expect(result).toBe(true);
  expect(fs.pathExistsSync(pngPath)).toBe(true);
});

test('save jpeg -- no image', () => {
  const result = saveImageAsJpegSync(jpegPath, 1.0);
  expect(result).toBe(false);
  expect(fs.pathExistsSync(jpegPath)).toBe(false);
});

test('save png -- no image', () => {
  const result = saveImageAsPngSync(pngPath);
  expect(result).toBe(false);
  expect(fs.pathExistsSync(pngPath)).toBe(false);
});

test('put image -- non-exist', () => {
  expect(putImageSync('/non/exist/path')).toBe(false);
});
