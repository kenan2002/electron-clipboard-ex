export function readFilePaths(): string[];

export function writeFilePaths(filePaths: string[]): string[];

export function clear(): void;

export function saveImageAsJpegSync(targetPath: string, compressionFactor: number): boolean;

export function saveImageAsJpeg(targetPath: string, compressionFactor: number): Promise<boolean>;

export function saveImageAsPngSync(targetPath: string): boolean;

export function saveImageAsPng(targetPath: string): Promise<boolean>;

export function putImageSync(imagePath: string): boolean;

export function putImage(imagePath: string): Promise<boolean>;
