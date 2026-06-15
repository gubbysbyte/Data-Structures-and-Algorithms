import { useEffect, useState } from "react";
import type { NewsDigest } from "./types";

/**
 * Format an ISO 8601 timestamp into a localized English date and time string.
 *
 * @param iso - An ISO 8601 timestamp string (for example: "2024-03-25T12:34:56Z")
 * @returns A string representing the input date formatted for the "en" locale using medium date and short time styles
 */
function formatTime(iso: string) {
  return new Intl.DateTimeFormat("en", {
    dateStyle: "medium",
    timeStyle: "short"
  }).format(new Date(iso));
}

/**
 * Root React component for the Tech Innovation Daily application.
 *
 * Fetches the news digest on mount (safely avoiding updates after unmount) and renders
 * one of: a loading screen while fetching, an error/fallback screen if no digest is available,
 * or the full dashboard (hero + signal chips + featured story + trending bento grid) when data is present.
 *
 * @returns The component's JSX element representing the app UI.
 */
function App() {
  const [digest, setDigest] = useState<NewsDigest | null>(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    let active = true;

    window.newsDesk
      .getDigest()
      .then((nextDigest) => {
        if (!active) {
          return;
        }
        setDigest(nextDigest);
      })
      .catch((fetchError: Error) => {
        if (!active) {
          return;
        }
        setError(fetchError.message);
      })
      .finally(() => {
        if (active) {
          setLoading(false);
        }
      });

    return () => {
      active = false;
    };
  }, []);

  if (loading) {
    return (
      <main className="app-shell loading-shell">
        <div className="loading-orb" />
        <p>Collecting today&apos;s innovation brief...</p>
      </main>
    );
  }

  if (!digest) {
    return (
      <main className="app-shell loading-shell">
        <p>Couldn&apos;t load the digest.</p>
        {error ? <span>{error}</span> : null}
      </main>
    );
  }

  return (
    <main className="app-shell">
      <div className="background-glow glow-left" />
      <div className="background-glow glow-right" />

      <section className="hero-row">
        <div className="headline-panel">
          <div className="eyebrow-row">
            <span className="eyebrow">Tech Innovation Daily</span>
            <span className="timestamp">Updated {formatTime(digest.generatedAt)}</span>
          </div>
          <h1>Daily trending tech stories, shaped into a calm desktop dashboard.</h1>
          <p>
            Track AI, robotics, startups, climate tech, and future-of-work headlines
            in a high-contrast bento experience designed for Windows and macOS.
          </p>

          <div className="signal-row">
            {digest.signals.map((signal) => (
              <div className={`signal-chip ${signal.tone}`} key={signal.label}>
                <span>{signal.label}</span>
                <strong>{signal.value}</strong>
              </div>
            ))}
          </div>
        </div>

        <a className="feature-card hero-card" href={digest.highlight.url} target="_blank" rel="noreferrer">
          <div
            className={`feature-image ${digest.highlight.accent}`}
            style={{ backgroundImage: `linear-gradient(135deg, rgba(8, 15, 28, 0.18), rgba(8, 15, 28, 0.76)), url(${digest.highlight.image})` }}
          />
          <div className="feature-content">
            <div className="card-tag-row">
              <span className="card-tag">{digest.highlight.category}</span>
              <span className="card-source">{digest.highlight.source}</span>
            </div>
            <h2>{digest.highlight.title}</h2>
            <p>{digest.highlight.summary}</p>
            <div className="card-footer">
              <span>{digest.highlight.mood}</span>
              <span>{formatTime(digest.highlight.publishedAt)}</span>
            </div>
          </div>
        </a>
      </section>

      <section className="bento-grid">
        {digest.trending.map((story, index) => (
          <a
            key={story.id}
            href={story.url}
            target="_blank"
            rel="noreferrer"
            className={`news-card span-${(index % 3) + 1}`}
          >
            <div
              className={`news-card-image ${story.accent}`}
              style={{ backgroundImage: `linear-gradient(180deg, rgba(4, 11, 22, 0.1), rgba(4, 11, 22, 0.85)), url(${story.image})` }}
            />
            <div className="news-card-copy">
              <div className="card-tag-row">
                <span className="card-tag soft">{story.category}</span>
                <span className="card-source">{story.source}</span>
              </div>
              <h3>{story.title}</h3>
              <p>{story.summary}</p>
              <div className="card-footer">
                <span>{story.mood}</span>
                <span>{formatTime(story.publishedAt)}</span>
              </div>
            </div>
          </a>
        ))}

        <aside className="mini-panel">
          <span className="eyebrow">How Live News Works</span>
          <h3>Add your API key and the feed becomes live.</h3>
          <p>
            Set `GNEWS_API_KEY` or `NEWS_API_KEY` before launching Electron.
            Without a key, the app falls back to an elegant demo digest so the
            layout still feels complete.
          </p>
        </aside>

        <aside className="mini-panel bright-panel">
          <span className="eyebrow">Platform Fit</span>
          <h3>Built for wide desktop canvases.</h3>
          <p>
            Electron packages for Windows and macOS, while the responsive grid keeps
            the editorial bento feel intact on smaller laptop screens too.
          </p>
        </aside>
      </section>
    </main>
  );
}

export default App;
