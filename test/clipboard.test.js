const {readFilePaths, writeFilePaths} = require('..');

const getMockPaths = () => {
  if (process.platform === 'win32') {
    return [
      'C:\\Windows\\mock.dll',
      'D:\\中文路径\\中文文件名.jpg',
    ];
  }

  return [
    '/Users/x/a.txt',
    '/中文路径/中文文件名.jpg',
  ];
};

test('write & read file paths', () => {
  const paths = getMockPaths();
  writeFilePaths(paths);
  expect(readFilePaths()).toEqual(paths);
});

test('write & read empty paths', () => {
  writeFilePaths([]);
  expect(readFilePaths()).toEqual([]);
});

test('write empty args -- throw', () => {
  expect(() => {
    writeFilePaths();
  }).toThrow();
});

test('write non-array -- throw', () => {
  expect(() => {
    writeFilePaths('string');
  }).toThrow();
});

test('write empty path -- throw', () => {
  expect(() => {
    writeFilePaths(['']);
  }).toThrow();
});

test('write non-string path -- throw', () => {
  expect(() => {
    writeFilePaths([1]);
  }).toThrow();
});
