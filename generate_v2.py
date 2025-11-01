#!/usr/bin/env python3
"""
競技プログラミングテンプレート生成スクリプト v2
より柔軟な入力形式の解析に対応
"""

import os
import sys
import re
from typing import List, Tuple, Dict

class InputParser:
    """入力形式の解析器"""

    def __init__(self):
        self.variables = []  # [(変数名, 型, 宣言, 入力コード)]
        self.seen_vars = set()  # 既に宣言済みの変数

    def parse_from_format(self, format_text: str):
        """入力形式テキストから解析"""
        lines = format_text.strip().split('\n')

        for line in lines:
            line = line.strip()
            if not line or line.startswith('#'):
                continue

            # クエリ形式の検出
            if 'queries' in line.lower() or 'query' in line.lower():
                self._parse_query_format(line)
            # 配列形式の検出
            elif '[' in line:
                self._parse_array_format(line)
            # グリッド形式の検出
            elif 'grid' in line.lower() or 'board' in line.lower():
                self._parse_grid_format(line)
            # 通常の変数
            else:
                self._parse_simple_format(line)

    def parse_from_sample(self, sample_input: str):
        """サンプル入力から推論"""
        lines = sample_input.strip().split('\n')

        if not lines:
            return

        # 最初の行を解析
        first_line = lines[0].strip().split()

        if len(first_line) == 1:
            # 単一の値
            val = first_line[0]
            if val.isdigit():
                if len(lines) > 1:
                    # Nの後に配列やクエリが続くパターン
                    n = int(val)
                    self._add_variable('n', 'int', 'int n', 'cin >> n')

                    # 2行目を確認
                    second_line = lines[1].strip()
                    if len(second_line.split()) == n:
                        # N個の要素
                        self._add_variable('a', 'vi', 'vi a(n)', 'cin >> a')
                    elif not second_line[0].isdigit():
                        # 文字列
                        self._add_variable('s', 'string', 'string s', 'cin >> s')
                else:
                    self._add_variable('n', 'int', 'int n', 'cin >> n')
            else:
                # 文字列
                self._add_variable('s', 'string', 'string s', 'cin >> s')

        elif len(first_line) == 2:
            # 2つの値（N, M や H, W など）
            if all(x.isdigit() for x in first_line):
                vars = ['n', 'm'] if int(first_line[0]) > 10 else ['h', 'w']
                self._add_variable(vars[0], 'int', f'int {vars[0]}', f'cin >> {vars[0]}')
                self._add_variable(vars[1], 'int', f'int {vars[1]}', f'cin >> {vars[1]}')

                # グリッドかどうかチェック
                if len(lines) > 1 and vars[0] == 'h':
                    if len(lines[1]) == int(first_line[1]):
                        # グリッド
                        self._add_variable('grid', 'vs', 'vs grid(h)', 'rep(i, h) cin >> grid[i]')

    def _parse_simple_format(self, line: str):
        """単純な変数の解析（N K など）"""
        tokens = line.split()

        for token in tokens:
            token = token.strip()
            if not token or token in self.seen_vars:
                continue

            var_name = token.lower()

            # 型の推定
            if var_name in ['n', 'm', 'k', 'h', 'w', 'q', 't']:
                var_type = 'int'
            elif var_name in ['x', 'y', 'l', 'r']:
                var_type = 'll'
            elif var_name == 's':
                var_type = 'string'
            else:
                var_type = 'int'

            self._add_variable(var_name, var_type, f'{var_type} {var_name}', f'cin >> {var_name}')

    def _parse_array_format(self, line: str):
        """配列形式の解析（A[N]、[A1, A2, ..., An]など）"""
        # A[N] 形式
        match = re.match(r'([A-Za-z]+)\[([A-Za-z]+)\]', line)
        if match:
            array_name = match.group(1).lower()
            size_var = match.group(2).lower()

            # サイズ変数が未定義なら追加
            if size_var not in self.seen_vars:
                self._add_variable(size_var, 'int', f'int {size_var}', f'cin >> {size_var}')

            # 配列の型を決定
            array_type = 'vll' if array_name in ['x', 'y'] else 'vi'
            self._add_variable(array_name, array_type, f'{array_type} {array_name}({size_var})', f'cin >> {array_name}')

        # [A1, A2, ..., An] 形式
        match = re.match(r'\[([A-Za-z])1.*?([A-Za-z])n\]', line, re.IGNORECASE)
        if match:
            array_name = match.group(1).lower()
            size_var = 'n'

            if size_var not in self.seen_vars:
                self._add_variable(size_var, 'int', f'int {size_var}', f'cin >> {size_var}')

            array_type = 'vll' if array_name in ['x', 'y'] else 'vi'
            self._add_variable(array_name, array_type, f'{array_type} {array_name}({size_var})', f'cin >> {array_name}')

    def _parse_query_format(self, line: str):
        """クエリ形式の解析"""
        # Q queries: type x y のような形式
        if 'queries' in line.lower():
            # Q個のクエリ
            if 'q' not in self.seen_vars:
                self._add_variable('q', 'int', 'int q', 'cin >> q')

            # クエリの形式を推定
            if ':' in line:
                query_format = line.split(':')[1].strip()
                tokens = query_format.split()

                # クエリ処理のループを追加
                loop_code = ['rep(i, q) {']

                for token in tokens:
                    if token in ['type', 't']:
                        loop_code.append('    int type;')
                        loop_code.append('    cin >> type;')
                    elif token in ['l', 'r', 'x', 'y', 'a', 'b']:
                        var_type = 'll' if token in ['x', 'y'] else 'int'
                        loop_code.append(f'    {var_type} {token};')
                        loop_code.append(f'    cin >> {token};')

                loop_code.append('    // TODO: クエリ処理')
                loop_code.append('}')

                self._add_variable('_query_loop', '_special', '', '\n    '.join(loop_code))

    def _parse_grid_format(self, line: str):
        """グリッド形式の解析"""
        # Grid[H][W] や H W grid など
        if 'grid' in line.lower():
            # H, Wを追加
            if 'h' not in self.seen_vars:
                self._add_variable('h', 'int', 'int h', 'cin >> h')
            if 'w' not in self.seen_vars:
                self._add_variable('w', 'int', 'int w', 'cin >> w')

            # グリッドを追加
            self._add_variable('grid', 'vs', 'vs grid(h)', 'rep(i, h) cin >> grid[i]')

    def _add_variable(self, name: str, var_type: str, declaration: str, input_code: str):
        """変数を追加"""
        if name not in self.seen_vars:
            self.variables.append((name, var_type, declaration, input_code))
            if name != '_query_loop':  # 特殊なものは記録しない
                self.seen_vars.add(name)

    def generate_code(self) -> Tuple[List[str], List[str]]:
        """宣言と入力コードを生成"""
        declarations = []
        input_codes = []

        for name, var_type, declaration, input_code in self.variables:
            if declaration:
                declarations.append(f'    {declaration};')
            if input_code:
                input_codes.append(f'    {input_code}')

        return declarations, input_codes


class TemplateGenerator:
    """テンプレート生成器"""

    def __init__(self):
        self.parser = InputParser()

    def generate(self, input_spec: str, filename: str = "solution.cc") -> str:
        """テンプレートを生成"""

        # 入力形式を解析
        # サンプル入力っぽい場合
        if '\n' in input_spec and all(
            line.strip() == '' or line.strip()[0].isdigit() or line.strip()[0].isalpha()
            for line in input_spec.split('\n')
        ):
            self.parser.parse_from_sample(input_spec)
        else:
            # 形式記述の場合
            self.parser.parse_from_format(input_spec)

        # コードを生成
        declarations, input_codes = self.parser.generate_code()

        # テンプレートを読み込み
        template_path = os.path.join(os.path.dirname(__file__), 'lib2/template.cc')
        with open(template_path, 'r') as f:
            template = f.read()

        # solve関数の中身を生成
        solve_lines = []

        if declarations:
            for decl in declarations:
                solve_lines.append(decl)
            solve_lines.append('')

        if input_codes:
            solve_lines.append('    // 入力')
            for code in input_codes:
                solve_lines.append(code)
            solve_lines.append('')

        solve_lines.append('    // TODO: 問題を解く処理')
        solve_lines.append('')
        solve_lines.append('    // 出力')
        solve_lines.append('    ')

        # テンプレート内のsolve関数を置換
        lines = template.split('\n')
        result_lines = []
        in_solve = False

        for line in lines:
            if 'void solve()' in line:
                in_solve = True
                result_lines.append(line)
                result_lines.extend(solve_lines)
                continue

            if in_solve:
                if line.strip() == '}':
                    in_solve = False
                    result_lines.append(line)
                continue

            result_lines.append(line)

        # ファイルに保存
        with open(filename, 'w') as f:
            f.write('\n'.join(result_lines))

        return filename


def main():
    """メイン関数"""
    print("=" * 60)
    print("競技プログラミング テンプレート生成ツール v2")
    print("=" * 60)
    print()

    # ファイル名
    filename = input("ファイル名 (デフォルト: solution.cc): ").strip()
    if not filename:
        filename = "solution.cc"
    if not filename.endswith('.cc'):
        filename += '.cc'

    print()
    print("入力形式を指定してください")
    print()
    print("【方法1】形式を記述")
    print("  例: N K")
    print("      A[N]")
    print("      Q queries: l r")
    print()
    print("【方法2】サンプル入力をペースト")
    print("  例: 5 3")
    print("      1 2 3 4 5")
    print()
    print("入力を終了するには空行を2回入力してください")
    print("-" * 40)

    lines = []
    empty_count = 0

    while True:
        line = input()
        if not line:
            empty_count += 1
            if empty_count >= 2:
                break
            lines.append(line)
        else:
            empty_count = 0
            lines.append(line)

    if not lines or all(not line for line in lines):
        print("❌ 入力が指定されていません")
        return

    input_spec = '\n'.join(lines)

    # テンプレート生成
    generator = TemplateGenerator()
    generator.generate(input_spec, filename)

    print()
    print(f"✅ テンプレートを生成しました: {filename}")

    # 生成内容を表示
    declarations, input_codes = generator.parser.generate_code()
    if declarations or input_codes:
        print()
        print("生成された入力処理:")
        print("-" * 40)
        for decl in declarations:
            print(decl)
        if declarations and input_codes:
            print()
        for code in input_codes:
            print(code)


if __name__ == "__main__":
    main()