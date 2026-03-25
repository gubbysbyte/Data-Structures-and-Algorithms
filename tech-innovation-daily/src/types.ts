export type NewsCard = {
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

export type NewsDigest = {
  generatedAt: string;
  highlight: NewsCard;
  trending: NewsCard[];
  signals: { label: string; value: string; tone: string }[];
};

declare global {
  interface Window {
    newsDesk: {
      getDigest: () => Promise<NewsDigest>;
    };
  }
}
