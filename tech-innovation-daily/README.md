# Tech Innovation Daily

Tech Innovation Daily is a desktop app for Windows and macOS that brings daily innovation headlines into a premium bento-card dashboard. It is built with Electron, React, TypeScript, and Vite.

## Highlights

- Cross-platform desktop experience for Windows and macOS
- Beautiful editorial bento layout for trending innovation stories
- Live news support through `GNEWS_API_KEY` or `NEWS_API_KEY`
- Graceful fallback digest when no API key is configured
- Electron packaging support through `electron-builder`

## Stack

- Electron
- React
- TypeScript
- Vite
- electron-builder

## Getting started

```bash
npm install
npm run dev
```

## Environment setup

Copy `.env.example` to `.env` and add your API key:

```bash
GNEWS_API_KEY=your_key_here
```

The app also accepts `NEWS_API_KEY`.

## Build for production

```bash
npm run build
```

## Package the desktop app

```bash
npm run dist
```

Note: on some Windows setups, installer packaging may require elevated symlink/code-sign tooling permissions. If that happens, the unpacked app output can still be generated successfully.

## Project structure

```text
electron/        Electron main process and preload bridge
src/             React UI and styles
dist/            Production web build output
dist-electron/   Compiled Electron files
```

## License

This project is available under the MIT License. See `LICENSE`.
