#!/usr/bin/env python3
"""
AtCoder テンプレート生成ツール
複数の入力方法に対応：
1. 入力形式の記述
2. サンプル入力
3. AtCoderのURLから取得（オプション）
"""

import os
import sys
import re
import subprocess
from typing import List, Tuple, Optional

class SmartInputParser:
    """スマート入力パーサー"""

    def __init__(self):
        self.lines = []  # 生成するコード行

    def parse(self, input_text: str) -> List[str]:
        """入力テキストを解析してコードを生成"""
        self.lines = []

        # 入力を正規化
        input_text = input_text.strip()

        # ケース1: 単純な数値入力（N, N K, N M K など）
        if re.match(r'^[A-Z](\s+[A-Z])*$', input_text.upper()):
            return self._parse_simple_vars(input_text)

        # ケース2: 構造化された入力
        lines = input_text.split('\n')

        for i, line in enumerate(lines):
            line = line.strip()
            if not line:
                continue

            # 配列記法の検出
            if self._is_array_notation(line):
                self._parse_array(line, i, lines)
            # グリッド記法の検出
            elif self._is_grid_notation(line):
                self._parse_grid(line, i, lines)
            # クエリ記法の検出
            elif self._is_query_notation(line):
                self._parse_query(line, i, lines)
            # サンプル入力の自動検出
            elif self._looks_like_sample(line):
                return self._parse_sample(lines)
            # 通常の変数
            else:
                self._parse_line_vars(line)

        return self.lines

    def _parse_simple_vars(self, text: str) -> List[str]:
        """単純な変数（N K など）"""
        vars = text.lower().split()
        result = []

        # 宣言
        for var in vars:
            if var in ['x', 'y', 'l', 'r']:
                result.append(f'    ll {var};')
            else:
                result.append(f'    int {var};')

        result.append('')
        result.append('    // 入力')

        # 入力
        result.append(f'    cin >> {" >> ".join(vars)};')

        return result

    def _is_array_notation(self, line: str) -> bool:
        """配列記法かどうか判定"""
        patterns = [
            r'^\w+\[\w+\]',           # A[N]
            r'^\[\w+1.*\w+n\]',       # [A1, ..., An]
            r'^\w+_1.*\w+_n',         # A_1 ... A_n
        ]
        return any(re.match(p, line, re.IGNORECASE) for p in patterns)

    def _parse_array(self, line: str, index: int, all_lines: List[str]):
        """配列の解析"""
        # A[N] 形式
        match = re.match(r'^(\w+)\[(\w+)\]', line)
        if match:
            array_name = match.group(1).lower()
            size_var = match.group(2).lower()

            # 前の行でサイズ変数が定義されているか確認
            if index > 0 and size_var.upper() in all_lines[index-1]:
                pass  # 既に処理済み
            else:
                self.lines.append(f'    int {size_var};')
                self.lines.append(f'    cin >> {size_var};')

            array_type = 'vll' if array_name in ['x', 'y'] else 'vi'
            self.lines.append(f'    {array_type} {array_name}({size_var});')
            self.lines.append(f'    cin >> {array_name};')

    def _is_grid_notation(self, line: str) -> bool:
        """グリッド記法かどうか判定"""
        return 'grid' in line.lower() or re.match(r'^s_1.*s_\w+', line, re.IGNORECASE)

    def _parse_grid(self, line: str, index: int, all_lines: List[str]):
        """グリッドの解析"""
        # 前の行でH Wが定義されているか確認
        if index > 0:
            prev_line = all_lines[index-1].upper()
            if 'H' in prev_line and 'W' in prev_line:
                pass  # H Wは処理済み
            else:
                self.lines.append('    int h, w;')
                self.lines.append('    cin >> h >> w;')
        else:
            self.lines.append('    int h, w;')
            self.lines.append('    cin >> h >> w;')

        self.lines.append('    vs grid(h);')
        self.lines.append('    rep(i, h) cin >> grid[i];')

    def _is_query_notation(self, line: str) -> bool:
        """クエリ記法かどうか判定"""
        return 'quer' in line.lower() or re.match(r'^Q$', line)

    def _parse_query(self, line: str, index: int, all_lines: List[str]):
        """クエリの解析"""
        self.lines.append('    int q;')
        self.lines.append('    cin >> q;')
        self.lines.append('    ')
        self.lines.append('    rep(query_id, q) {')

        # 次の行を見てクエリの形式を推定
        if index + 1 < len(all_lines):
            next_line = all_lines[index + 1].strip()
            tokens = next_line.split()

            for token in tokens:
                token_lower = token.lower()
                if token_lower in ['type', 't']:
                    self.lines.append('        int type;')
                    self.lines.append('        cin >> type;')
                elif token_lower in ['l', 'r']:
                    self.lines.append('        int l, r;')
                    self.lines.append('        cin >> l >> r;')
                    break
                elif token_lower in ['x', 'y']:
                    self.lines.append('        ll x, y;')
                    self.lines.append('        cin >> x >> y;')
                    break
        else:
            self.lines.append('        // TODO: クエリの入力')

        self.lines.append('        ')
        self.lines.append('        // TODO: クエリの処理')
        self.lines.append('    }')

    def _looks_like_sample(self, line: str) -> bool:
        """サンプル入力っぽいか判定"""
        tokens = line.split()
        return all(self._is_number_or_simple_string(t) for t in tokens)

    def _is_number_or_simple_string(self, s: str) -> bool:
        """数値または単純な文字列か判定"""
        try:
            int(s)
            return True
        except:
            return len(s) < 20 and s.isalnum()

    def _parse_sample(self, lines: List[str]) -> List[str]:
        """サンプル入力から推論"""
        result = []

        if not lines:
            return result

        first_line = lines[0].strip().split()

        # 最初の行が1つの数値
        if len(first_line) == 1 and first_line[0].isdigit():
            n = int(first_line[0])
            result.append('    int n;')
            result.append('    cin >> n;')

            if len(lines) > 1:
                second_line = lines[1].strip()
                second_tokens = second_line.split()

                if len(second_tokens) == n:
                    # N個の要素
                    result.append('    vi a(n);')
                    result.append('    cin >> a;')
                elif len(second_line) == n and not second_line[0].isdigit():
                    # 長さNの文字列
                    result.append('    string s;')
                    result.append('    cin >> s;')

        # 最初の行が2つの数値
        elif len(first_line) == 2 and all(x.isdigit() for x in first_line):
            val1, val2 = map(int, first_line)

            if val1 <= 1000 and val2 <= 1000:
                # おそらくH W（グリッド）
                if len(lines) > val1:
                    result.append('    int h, w;')
                    result.append('    cin >> h >> w;')
                    result.append('    vs grid(h);')
                    result.append('    rep(i, h) cin >> grid[i];')
                else:
                    # N M（通常）
                    result.append('    int n, m;')
                    result.append('    cin >> n >> m;')
            else:
                # N K（通常）
                result.append('    int n, k;')
                result.append('    cin >> n >> k;')

        # 最初の行が3つ以上の数値
        elif len(first_line) >= 3 and all(x.isdigit() for x in first_line):
            vars = ['n', 'm', 'k'][:len(first_line)]
            for var in vars:
                result.append(f'    int {var};')
            result.append(f'    cin >> {" >> ".join(vars)};')

        return result

    def _parse_line_vars(self, line: str):
        """通常の変数行を解析"""
        tokens = line.split()

        declarations = []
        vars = []

        for token in tokens:
            if not token or not token[0].isalpha():
                continue

            var = token.lower()
            if var in ['x', 'y', 'l', 'r']:
                declarations.append(f'll {var}')
            else:
                declarations.append(f'int {var}')
            vars.append(var)

        if declarations:
            self.lines.append(f'    {", ".join(declarations)};')
            self.lines.append(f'    cin >> {" >> ".join(vars)};')


def generate_template(input_spec: str, filename: str = "solution.cc"):
    """テンプレートを生成"""

    # パーサーを使って入力コードを生成
    parser = SmartInputParser()
    input_lines = parser.parse(input_spec)

    # テンプレートを読み込み
    template_path = os.path.join(os.path.dirname(__file__), 'lib2/template.cc')
    if not os.path.exists(template_path):
        template_path = os.path.join(os.path.dirname(__file__), 'template.cc')

    with open(template_path, 'r') as f:
        template = f.read()

    # solve関数の内容を生成
    solve_content = input_lines + [
        '',
        '    // TODO: 問題を解く',
        '    ',
        '    // 出力',
        '    '
    ]

    # テンプレート内のsolve関数を置換
    lines = template.split('\n')
    result = []
    in_solve = False
    solve_found = False

    for line in lines:
        if 'void solve()' in line:
            in_solve = True
            solve_found = True
            result.append(line)
            result.extend(solve_content)
            continue

        if in_solve:
            if line.strip() == '}':
                in_solve = False
                result.append(line)
            continue

        result.append(line)

    # ファイルに保存
    with open(filename, 'w') as f:
        f.write('\n'.join(result))

    print(f'✅ Generated: {filename}')

    # 生成内容をプレビュー
    if input_lines:
        print('\n📝 Input handling:')
        print('-' * 40)
        for line in input_lines[:10]:  # 最初の10行だけ表示
            print(line)
        if len(input_lines) > 10:
            print('    ...')


def main():
    if len(sys.argv) > 1:
        # コマンドライン引数モード
        filename = sys.argv[1] if not sys.argv[1].startswith('-') else 'solution.cc'

        if '--help' in sys.argv or '-h' in sys.argv:
            print('Usage:')
            print('  python atgen.py [filename]  # Interactive mode')
            print('  echo "N K" | python atgen.py abc.cc  # Pipe mode')
            return

        # パイプからの入力をチェック
        if not sys.stdin.isatty():
            input_spec = sys.stdin.read()
            generate_template(input_spec, filename)
            return

    # インタラクティブモード
    print('AtCoder Template Generator')
    print('=' * 40)
    print()

    filename = input('Filename (default: solution.cc): ').strip()
    if not filename:
        filename = 'solution.cc'
    if not filename.endswith('.cc'):
        filename += '.cc'

    print()
    print('Enter input format or sample input:')
    print('(Press Ctrl+D or enter "END" to finish)')
    print('-' * 40)

    lines = []
    while True:
        try:
            line = input()
            if line == 'END':
                break
            lines.append(line)
        except EOFError:
            break

    if lines:
        input_spec = '\n'.join(lines)
        generate_template(input_spec, filename)
    else:
        print('❌ No input specified')


if __name__ == '__main__':
    main()