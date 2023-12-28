#include <iostream>
#include <set>
#include <map>
#include "Screen.h"
#include "Table.h"
#include "TextBox.h"
#include "Button.h"
#include "TextLabel.h"

std::string alph = "ABCDEFGHIGKLMNOP";
std::vector<std::vector<std::string>> a(10, std::vector<std::string>(10, " "));
std::vector<std::vector<int>> b(10, std::vector<int>(10, 0));

std::set<std::set<std::pair<std::string, std::string>>> data_res;
std::vector<std::pair<std::string, std::string>> strings;

void bt(int ind, std::set<std::pair<std::string, std::string>> res, std::map<std::pair<std::string, std::string>, std::vector<int>> mp, std::vector<bool> used) {
    bool flag = true;
    for (int i = 0; i < used.size(); ++i) {
        if (a[i + 1][0] == "1" && !used[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {

        if (data_res.empty()) {
            data_res.insert(res);
        } else {
            int perfect_size = 0;
            for (auto u : *data_res.begin()) {
                perfect_size += u.first.size();
            }

            int my_size = 0;
            for (auto u : res) {
                my_size += u.first.size();
            }

            if (my_size < perfect_size) {
                data_res.clear();
                data_res.insert(res);
            } else if (my_size == perfect_size) {
                data_res.insert(res);
            }
        }
        return;

    }
    for (int j = ind; j < strings.size(); ++j) {
        auto u = strings[j];
        bool is_covered = false;
        for (auto e : mp[u]) {
            if (!used[e]) {
                is_covered = true;
                break;
            }
        }
        if (is_covered) {
            std::vector<bool> usd = used;
            for (auto e : mp[u]) {
                usd[e] = true;
            }
            res.insert(u);
            bt(j + 1, res, mp, usd);
            res.erase(u);
        }
    }
}

std::vector<std::string> table_res;

void result() {
    std::vector<bool> used(a.size() - 1, false);
    std::map<std::pair<std::string, std::string>, std::vector<int>> mp;
    for (int i = 1; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            if (!b[i][j]) {
                mp[{ a[i][j], a[0][j] }].push_back(i - 1);
            }
        }
    }
    std::set<std::pair<std::string, std::string>> st;
    for (int i = 1; i < a.size(); ++i) {
        for (int j = 1; j < a[0].size(); ++j) {
            if (!b[i][j] && st.find({ a[i][j], a[0][j] }) == st.end()) {
                st.insert({ a[i][j], a[0][j] });
                strings.push_back({ a[i][j], a[0][j] });
            }
        }
    }
    bt(0, { }, mp, used);

    table_res.clear();
    for (auto u : data_res) {
        std::string res;
        for (auto e : u) {
            for (int i = 0; i < e.first.size(); ++i) {
                if (e.first[i] == '1') {
                    res += e.second[i];
                } else {
                    res += char(e.second[i] + 32);
                }
            }
            res += " v ";
        }
        res.pop_back();
        res.pop_back();
        res.pop_back();
        table_res.push_back(res);
    }
    TextLabel::GetInstance()->setStrings(table_res);
}

int pos = 1;
void fun(int len, int ind = 1) {
    if (ind == len + 1) {
        ++pos;
        if (pos != a.size()) {
            for (int j = 1; j <= len; ++j) {
                a[pos][j] = a[pos - 1][j];
            }
        }
        return;
    }
    for (int j = 0; j < 2; ++j) {
        a[pos][ind] = std::to_string(j);
        fun(len, ind + 1);
    }
}

std::vector<int> con;
void bt(int i, int j, int len, int cnt) {
    if (i == len) {
        std::string res;
        for (int k = 0; k < len; ++k) {
            res += alph[con[k]];
        }
        a[0].push_back(res);
        for (int k = 1; k < a.size(); ++k) {
            std::string tec;
            for (int y = 0; y < len; ++y) {
                tec += a[k][con[y] + 1];
            }
            a[k].push_back(tec);
        }
        return;
    }
    for (int k = j; k < cnt; ++k) {
        con[i] = k;
        bt(i + 1, k + 1, len, cnt);
    }
}
void delete_crossed() {
    for (int ind = 0; ind < a[0].size(); ++ind) {
        std::set<std::string> st;
        for (int i = 1; i < a.size(); ++i) {
            if (b[i][ind] == 1) {
                st.insert(a[i][ind]);
            }
        }
        for (int i = 1; i < a.size(); ++i) {
            if (b[i][ind] != 0) continue;
            if (st.find(a[i][ind]) != st.end()) {
                b[i][ind] = 2;
            }
        }
    }
}
bool Search(std::string data, std::string regex) {
    for (auto u : regex) {
        bool flag = true;
        for (int i = 0; i < data.size(); ++i) {
            if (data[i] == u) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return false;
        }
    }
    return true;
}
void absorption() {
    for (int i = 1; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            if (!b[i][j]) {
                for (int k = j + 1; k < a[i].size(); ++k) {
                    if (Search(a[0][k], a[0][j])) {
                        b[i][k] = 3;
                    }
                }
            }
        }
    }
}
void crossed() {
    for (int i = 1; i < a.size(); ++i) {
        if (a[i][0] == "0") {
            for (int j = 0; j < a[i].size(); ++j) {
                b[i][j] = 1;
            }
        }
    }
}
bool used[4];
void on_Click(std::string cnt, std::string fun_number, Table& table) {
    if (cnt.empty() || fun_number.empty()) {
        return;
    }
    for (int i = 0; i < 4; ++i) {
        used[i] = false;
    }
    int cnt_num = std::stoi(cnt);
    long long fn = std::stol(fun_number);
    a.assign((1 << cnt_num) + 1, std::vector<std::string>(cnt_num + 1, " "));
    con.assign(cnt_num, 0);
    for (int i = 1; i <= cnt_num; ++i) {
        a[0][i] = alph[i - 1];
    }
    a[0][0] = "f()";
    std::string function_res = "";
    while (fn) {
        function_res += char((fn & 1) + '0');
        fn /= 2;
    }

    if (function_res.size() > 1 << cnt_num) {
        return;
    }

    while (function_res.size() != a.size() - 1) {
        function_res.push_back('0');
    }
    std::reverse(function_res.begin(), function_res.end());
    for (int i = 0; i < function_res.size(); ++i) {
        a[i + 1][0] = function_res[i];
    }
    pos = 1;
    fun(cnt_num);
    for (int i = 2; i <= cnt_num; ++i) {
        bt(0, 0, i, cnt_num);
    }
    b.assign(a.size(), std::vector<int>(a[0].size(), 0));
    table.setData(b, a);
}
int tec_ind = 0;
void next_Click(int ind, Table& table) {
    void (*f[4])() = { crossed,
    delete_crossed,
    absorption, result };
    if (!used[ind] && ind < 4) {
        ++tec_ind;
        used[ind] = true;
        f[ind]();
        table.setData(b, a);
    }
}

int main() {
    Screen::GetInstance()->Init();
    sf::RenderWindow* wnd = Screen::GetInstance()->window;

    Table table;
    sf::Font font;
    TextBox input;
    TextBox cnt;
    Button btn;
    Button next;

    font.loadFromFile("3270NerdFontMono-Regular.ttf");
    input.SetFont(font);
    cnt.SetFont(font);
    TextLabel::GetInstance()->Create(font);
    TextLabel::GetInstance()->SetColor();

    std::string title = "f number:";
    input.SetBackColor(sf::Color(205, 198, 165));
    cnt.SetBackColor(sf::Color(205, 198, 165));
    input.SetSize({ wnd->getSize().x * (float)0.19, wnd->getSize().y * (float)0.15 });
    cnt.SetSize({ wnd->getSize().x * (float)0.19, wnd->getSize().y * (float)0.15 });
    btn.SetBackColor(sf::Color(141, 159, 135));
    next.SetBackColor(sf::Color(141, 159, 135));
    btn.SetSize({ wnd->getSize().x * (float)0.19, wnd->getSize().y * (float)0.1 });
    next.SetSize({ wnd->getSize().x * (float)0.19, wnd->getSize().y * (float)0.1 });
    input.SetPosition({ wnd->getSize().x * (float)0.805, wnd->getSize().y * (float)0.01 });
    cnt.SetPosition({ wnd->getSize().x * (float)0.805, wnd->getSize().y * (float)0.17 });
    btn.SetPosition({ wnd->getSize().x * (float)0.805,  wnd->getSize().y * (float)0.33 });
    next.SetPosition({ wnd->getSize().x * (float)0.805,  wnd->getSize().y * (float)0.44 });
    input.SetTitle(font, title);
    std::string btnTitle = "start";
    std::string nextTitle = "next";
    btn.SetText(btnTitle, sf::Color::Black, font);
    next.SetText(nextTitle, sf::Color::Black, font);
    std::string cntTitle = "n cnt:";
    input.SetTitle(font, cntTitle);

    table.setData(b, a);

    sf::Image zhdun;
    zhdun.loadFromFile("zhdun.png");

    sf::Texture texture;
    texture.loadFromImage(zhdun);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    const sf::Vector2f defaultResolution = sf::Vector2f(512.0F, 512.0F);
    sprite.setScale((static_cast<float>(std::min(wnd->getSize().x, wnd->getSize().y)) / defaultResolution.x) * (float)0.4,
                    (static_cast<float>(std::min(wnd->getSize().x, wnd->getSize().y)) / defaultResolution.y) * (float)0.4);
    sprite.setPosition(wnd->getSize().x * 0.8, wnd->getSize().y * 0.6);

    bool is_update = true;
    while (wnd->isOpen()) {
        sf::Event event{};
        while (wnd->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                wnd->close();
            }
            // resize window
            if (event.type == sf::Event::Resized) {
                TextLabel::GetInstance()->Create(font);
                is_update = true;
                sf::Vector2u windowSize = sf::Vector2u(event.size.width, event.size.height);
                wnd->setView(sf::View(sf::Vector2f((float) windowSize.x / 2.f, (float) windowSize.y / 2.f),
                                      sf::Vector2f(windowSize)));
                sprite.setScale((static_cast<float>(std::min(wnd->getSize().x, wnd->getSize().y)) / defaultResolution.x) * (float)0.4,
                                (static_cast<float>(std::min(wnd->getSize().x, wnd->getSize().y)) / defaultResolution.y) * (float)0.4);
                sprite.setPosition(wnd->getSize().x * 0.8, wnd->getSize().y * 0.6);
                input.SetSize({ wnd->getSize().x * (float)0.19, wnd->getSize().y * (float)0.15 });
                btn.SetSize({ wnd->getSize().x * (float)0.19, wnd->getSize().y * (float)0.1 });
                next.SetSize({ wnd->getSize().x * (float)0.19, wnd->getSize().y * (float)0.1 });
                cnt.SetSize({ wnd->getSize().x * (float)0.19, wnd->getSize().y * (float)0.15 });


                input.SetPosition({ wnd->getSize().x * (float)0.805, wnd->getSize().y * (float)0.01 });
                cnt.SetPosition({ wnd->getSize().x * (float)0.805, wnd->getSize().y * (float)0.17 });
                btn.SetPosition({ wnd->getSize().x * (float)0.805,  wnd->getSize().y * (float)0.33 });
                next.SetPosition({ wnd->getSize().x * (float)0.805,  wnd->getSize().y * (float)0.44 });

                input.SetTitle(font, title);
                cnt.SetTitle(font, cntTitle);
            }
            if (event.type == sf::Event::TextEntered || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                is_update = true;
            }
        }
        if (btn.isMouseOver(*wnd)) {
            tec_ind = 0;
            is_update = true;
            data_res.clear();
            on_Click(cnt.get_text(), input.get_text(), table);
        }
        if (next.isMouseOver(*wnd)) {
            is_update = true;
            next_Click(tec_ind, table);
        }
        input.enter(event);
        cnt.enter(event);
        TextLabel::GetInstance()->Scroll(event, font);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            is_update = true;
            input.setActive(input.isMousOver(*wnd));
            cnt.setActive(cnt.isMousOver(*wnd));
            TextLabel::GetInstance()->setActive(TextLabel::GetInstance()->isMousOver(*wnd));
        }
        if (is_update) {
            is_update = false;
            wnd->clear(sf::Color::White);
            wnd->draw(sprite);
            input.Draw_To(*wnd);
            cnt.Draw_To(*wnd);
            table.DrawTo(*wnd, font, 0.8);
        }
        TextLabel::GetInstance()->drawTo(font);
        next.Draw_To(*wnd);
        btn.Draw_To(*wnd);
        wnd->display();
    }
    return 0;
}
