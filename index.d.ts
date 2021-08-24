/**
 * @returns {string[]} An Array of file paths in clipboard.
 */
export function readFilePaths(): string[];

/**
 * @param {string[]} filePaths An Array of file paths.
 * @returns {string[]} An Array of file paths that successfully written into clipboard.
 */
export function writeFilePaths(filePaths: string[]): string[];

/**
 * Clear clipboard.
 */
export function clear(): void;

/**
 * Save image in clipboard as a jpeg file.
 * @param {string} targetPath Target jpeg file path.
 * @param {number} compressionFactor A float number ranges 0-1.
 * @returns {boolean} True if the target jpeg file is created, false otherwise.
 */
export function saveImageAsJpegSync(targetPath: string, compressionFactor: number): boolean;

/**
 * Async version of `saveImageAsJpegSync`.
 * @param {string} targetPath
 * @param {number} compressionFactor
 * @returns {Promise<boolean>}
 * @see saveImageAsJpegSync
 */
export function saveImageAsJpeg(targetPath: string, compressionFactor: number): Promise<boolean>;

/**
 * Save image in clipboard as a png file.
 * @param {string} targetPath Target png file path.
 * @returns {boolean} True if the target png file is created, false otherwise.
 */
export function saveImageAsPngSync(targetPath: string): boolean;

/**
 * Async version of `saveImageAsPngSync`.
 * @param {string} targetPath
 * @returns {Promise<boolean>}
 * @see saveImageAsPngSync
 */
export function saveImageAsPng(targetPath: string): Promise<boolean>;

/**
 * Put an image into clipboard.
 * @param {string} imagePath The source image file path.
 * @returns {boolean} True is successfully done.
 */
export function putImageSync(imagePath: string): boolean;

/**
 * Async version of `putImageSync`.
 * @param {string} imagePath
 * @returns {Promise<boolean>}
 * @see putImageSync
 */
export function putImage(imagePath: string): Promise<boolean>;

/**
 * @returns {boolean} If clipboard has an image in it.
 */
export function hasImage(): boolean;
