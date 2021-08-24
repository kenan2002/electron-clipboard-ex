const path = require('path');
const fs = require('fs-extra');
const {
  clear,
  saveImageAsJpeg, saveImageAsPng, putImage,
  saveImageAsJpegSync, saveImageAsPngSync, putImageSync, hasImage
} = require('..');

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

test('save jpeg -- normal', async () => {
  expect(await putImage(sourceImage)).toBe(true);
  const result = await saveImageAsJpeg(jpegPath, 1.0);
  expect(result).toBe(true);
  expect(fs.pathExistsSync(jpegPath)).toBe(true);
});

test('save png -- normal', async () => {
  expect(await putImage(sourceImage)).toBe(true);
  const result = await saveImageAsPng(pngPath);
  expect(result).toBe(true);
  expect(fs.pathExistsSync(pngPath)).toBe(true);
});

test('save jpeg sync -- normal', () => {
  expect(putImageSync(sourceImage)).toBe(true);
  const result = saveImageAsJpegSync(jpegPath, 1.0);
  expect(result).toBe(true);
  expect(fs.pathExistsSync(jpegPath)).toBe(true);
});

test('save png sync -- normal', () => {
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

test('has image -- false', () => {
  expect(hasImage()).toBe(false);
});

test('has image -- true', () => {
  putImageSync(sourceImage);
  expect(hasImage()).toBe(true);
});
