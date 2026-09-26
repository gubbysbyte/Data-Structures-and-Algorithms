class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
    //         Normal character → directly add it to the answer.
    //         '(' → find the corresponding ')', extract the key, look it up in knowledge, and append the value.
    //         If the key doesn't exist → append "?".

        unordered_map<string, string> mp;

        for(auto &pair : knowledge){
            mp[pair[0]] = pair[1];
        }

        string new_ans = "";
        int m = s.length();

        for(int i = 0; i < m; i++){
            if(s[i] != '('){
                new_ans += s[i];
            }
            else{
                // find the key
                string matching_key = "";
                i++;

                while(s[i] != ')'){
                    matching_key += s[i];
                    i++;
                }

                if(mp.find(matching_key) != mp.end()){
                    new_ans += mp[matching_key];
                } else{
                    new_ans += '?';
                }
            }
        }

        return new_ans;

    }
};