import { app, BrowserWindow, ipcMain } from "electron";
import "dotenv/config";
import path from "node:path";

type NewsCard = {
  id: string;
  title: string;
  source: string;
  summary: string;
  url: string;
  publishedAt: string;
  category: string;
  mood: string;
  image: string;
  accent: string;
};

type NewsDigest = {
  generatedAt: string;
  highlight: NewsCard;
  trending: NewsCard[];
  signals: { label: string; value: string; tone: string }[];
};

const isDev = !app.isPackaged;

const fallbackDigest: NewsDigest = {
  generatedAt: new Date().toISOString(),
  highlight: {
    id: "fallback-highlight",
    title: "AI chips, robotics, and climate tech keep shaping the innovation cycle",
    source: "Curated Demo Feed",
    summary:
      "A resilient fallback digest keeps the app beautiful and informative even before an API key is added. Plug in your own news provider key to swap this preview with live stories.",
    url: "https://news.google.com/topics/CAAqJggKIiBDQkFTRWdvSUwyMHZNREU1WnpBU0JXVnVMVWRDS0FBUAE",
    publishedAt: new Date().toISOString(),
    category: "Daily Brief",
    mood: "Momentum",
    image:
      "https://images.unsplash.com/photo-1518770660439-4636190af475?auto=format&fit=crop&w=1200&q=80",
    accent: "from-cyan"
  },
  trending: [
    {
      id: "trend-1",
      title: "Humanoid robotics pilots move from labs into industrial workflows",
      source: "Curated Demo Feed",
      summary:
        "Automation stories are accelerating around warehouse support, manufacturing assistance, and safety-oriented copilots.",
      url: "https://news.google.com/home?hl=en-US&gl=US&ceid=US:en",
      publishedAt: new Date().toISOString(),
      category: "Robotics",
      mood: "Factory Shift",
      image:
        "https://images.unsplash.com/photo-1485827404703-89b55fcc595e?auto=format&fit=crop&w=1200&q=80",
      accent: "from-amber"
    },
    {
      id: "trend-2",
      title: "Edge AI devices are getting smaller, faster, and more energy-aware",
      source: "Curated Demo Feed",
      summary:
        "Founders are chasing on-device inference for privacy, speed, and offline-first product experiences.",
      url: "https://news.google.com/home?hl=en-US&gl=US&ceid=US:en",
      publishedAt: new Date().toISOString(),
      category: "Edge AI",
      mood: "On Device",
      image:
        "https://images.unsplash.com/photo-1581092335397-9583eb92d232?auto=format&fit=crop&w=1200&q=80",
      accent: "from-emerald"
    },
    {
      id: "trend-3",
      title: "Climate-tech funding keeps clustering around storage and grid intelligence",
      source: "Curated Demo Feed",
      summary:
        "Investors continue to watch battery innovation, transmission software, and industrial decarbonization signals.",
      url: "https://news.google.com/home?hl=en-US&gl=US&ceid=US:en",
      publishedAt: new Date().toISOString(),
      category: "Climate Tech",
      mood: "Grid Pulse",
      image:
        "https://images.unsplash.com/photo-1473341304170-971dccb5ac1e?auto=format&fit=crop&w=1200&q=80",
      accent: "from-rose"
    },
    {
      id: "trend-4",
      title: "Bioengineering and AI discovery stacks are converging faster",
      source: "Curated Demo Feed",
      summary:
        "Teams are pairing modeling, simulation, and lab automation to compress the path from idea to experiment.",
      url: "https://news.google.com/home?hl=en-US&gl=US&ceid=US:en",
      publishedAt: new Date().toISOString(),
      category: "BioTech",
      mood: "Lab Speed",
      image:
        "https://images.unsplash.com/photo-1532187643603-ba119ca4109e?auto=format&fit=crop&w=1200&q=80",
      accent: "from-violet"
    }
  ],
  signals: [
    { label: "Theme", value: "Applied AI", tone: "positive" },
    { label: "Heat", value: "Rising", tone: "warning" },
    { label: "Market", value: "Founder-led", tone: "neutral" }
  ]
};

/**
 * Create and show the main application BrowserWindow.
 *
 * Configures a window with fixed initial dimensions and minimum size, a dark background, and a macOS-friendly title bar. Enables webPreferences that use the bundled preload script, enforce context isolation, and disable Node integration. In development (when `isDev` and `VITE_DEV_SERVER_URL` are present) the window loads the dev server URL; otherwise it loads the packaged `dist/index.html`.
 */
function createWindow() {
  const window = new BrowserWindow({
    width: 1480,
    height: 980,
    minWidth: 1180,
    minHeight: 760,
    backgroundColor: "#07111f",
    titleBarStyle: process.platform === "darwin" ? "hiddenInset" : "default",
    webPreferences: {
      preload: path.join(__dirname, "preload.js"),
      contextIsolation: true,
      nodeIntegration: false
    }
  });

  if (isDev && process.env.VITE_DEV_SERVER_URL) {
    void window.loadURL(process.env.VITE_DEV_SERVER_URL);
  } else {
    void window.loadFile(path.join(__dirname, "../dist/index.html"));
  }
}

/**
 * Normalize a raw news API article into a consistent NewsCard with deterministic metadata.
 *
 * @param article - The raw article object from the news API; may contain fields such as `title`, `source`, `description`, `content`, `url`, `publishedAt`, `image`, or `urlToImage`.
 * @param index - The article's index in the returned list; used to form a stable `id` and to deterministically select `category`, `mood`, and `accent`.
 * @returns A NewsCard with `id`, `title`, `source`, `summary`, `url`, `publishedAt`, `category`, `mood`, `image`, and `accent`; any missing source/title/summary/url/publishedAt/image values are replaced with sensible defaults.
function normalizeArticle(article: any, index: number): NewsCard {
  const accents = ["from-cyan", "from-amber", "from-emerald", "from-rose", "from-violet"];
  const categories = ["AI", "Startups", "Climate Tech", "Robotics", "Future of Work"];
  const moods = ["Momentum", "Breakthrough", "Signal", "Frontier", "Watchlist"];

  return {
    id: `${article.title ?? "article"}-${index}`,
    title: article.title ?? "Untitled innovation story",
    source: article.source?.name ?? article.source?.title ?? "Unknown source",
    summary:
      article.description ??
      article.content?.slice(0, 180) ??
      "Fresh innovation coverage with concise details from the live feed.",
    url: article.url ?? "https://news.google.com/",
    publishedAt: article.publishedAt ?? new Date().toISOString(),
    category: categories[index % categories.length],
    mood: moods[index % moods.length],
    image:
      article.image ??
      article.urlToImage ??
      fallbackDigest.trending[index % fallbackDigest.trending.length].image,
    accent: accents[index % accents.length]
  };
}

/**
 * Fetches a news digest of technology-focused stories from the GNews API.
 *
 * If no API key is configured, the API returns no articles, or a network/error occurs, the function falls back to the bundled `fallbackDigest`.
 *
 * @returns A `NewsDigest` containing a `generatedAt` timestamp, a `highlight` article, an array of `trending` articles, and `signals`; returns `fallbackDigest` when no API key is available, when the fetched results are empty, or when an error occurs during retrieval.
 */
async function fetchNewsDigest(): Promise<NewsDigest> {
  const apiKey = process.env.GNEWS_API_KEY ?? process.env.NEWS_API_KEY;
  if (!apiKey) {
    return fallbackDigest;
  }

  const endpoint = new URL("https://gnews.io/api/v4/search");
  endpoint.searchParams.set("q", "technology innovation OR startups OR artificial intelligence");
  endpoint.searchParams.set("lang", "en");
  endpoint.searchParams.set("country", "us");
  endpoint.searchParams.set("max", "8");
  endpoint.searchParams.set("apikey", apiKey);

  try {
    const response = await fetch(endpoint, {
      headers: {
        "User-Agent": "TechInnovationDaily/1.0"
      }
    });

    if (!response.ok) {
      throw new Error(`News API request failed with status ${response.status}`);
    }

    const data = (await response.json()) as { articles?: any[] };
    const articles = data.articles?.slice(0, 5).map(normalizeArticle) ?? [];

    if (articles.length === 0) {
      return fallbackDigest;
    }

    return {
      generatedAt: new Date().toISOString(),
      highlight: articles[0],
      trending: articles.slice(1),
      signals: [
        { label: "Freshness", value: "Daily", tone: "positive" },
        { label: "Coverage", value: `${articles.length} stories`, tone: "neutral" },
        { label: "Source", value: "Live API", tone: "warning" }
      ]
    };
  } catch (error) {
    console.error("Falling back to demo digest.", error);
    return fallbackDigest;
  }
}

app.whenReady().then(() => {
  ipcMain.handle("news:getDigest", fetchNewsDigest);
  createWindow();

  app.on("activate", () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }
  });
});

app.on("window-all-closed", () => {
  if (process.platform !== "darwin") {
    app.quit();
  }
});
