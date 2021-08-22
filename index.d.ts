export function readFilePaths(): string[];

export function writeFilePaths(filePaths: string[]): string[];

export function clear(): void;

export function saveImageAsJpegSync(targetPath: string, compressionFactor: number): boolean;

export function saveImageAsPngSync(targetPath: string): boolean;

export function putImageSync(imagePath: string): boolean;
