class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        int freq[26] = {};

        for (char c : s) {
            freq[c - 'a']++;
        }

        string ans;

        // Try to match target as long as possible
        for (int i = 0; i < n; i++) {

            int x = target[i] - 'a';

            // We cannot match target[i]
            if (freq[x] == 0) {

                // Try to make this position greater
                for (int c = x + 1; c < 26; c++) {
                    if (freq[c] > 0) {

                        ans += char('a' + c);
                        freq[c]--;

                        // Put remaining characters
                        // in sorted order
                        for (int k = 0; k < 26; k++) {
                            ans += string(freq[k], 'a' + k);
                        }

                        return ans;
                    }
                }

                // Cannot make current position greater,
                // so we must backtrack.
                break;
            }

            // Match target[i]
            ans += target[i];
            freq[x]--;
        }

        /*
            We either:
            1. matched the whole target, or
            2. got stuck at some position.

            In either case, backtrack.
        */

        for (int i = ans.size() - 1; i >= 0; i--) {

            // Return ans[i] back to the frequency table
            freq[ans[i] - 'a']++;

            int x = target[i] - 'a';

            // Find smallest character > target[i]
            for (int c = x + 1; c < 26; c++) {

                if (freq[c] > 0) {

                    string result = ans.substr(0, i);

                    result += char('a' + c);
                    freq[c]--;

                    // Smallest possible suffix
                    for (int k = 0; k < 26; k++) {
                        result += string(freq[k], 'a' + k);
                    }

                    return result;
                }
            }
        }

        return "";
    }
};