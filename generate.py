#!/usr/bin/env python3
"""
競技プログラミングテンプレート生成スクリプト
入力形式を解析して、適切な入力処理コードを含むテンプレートを生成
"""

import os
import sys
import re

class TemplateGenerator:
    def __init__(self):
        self.variables = {}
        self.input_code = []
        self.declarations = []

    def parse_format(self, format_str):
        """入力形式を解析"""
        lines = format_str.strip().split('\n')

        for line in lines:
            self.parse_line(line)

    def parse_line(self, line):
        """1行の入力形式を解析"""
        tokens = line.split()

        for token in tokens:
            # 配列形式 [A1, A2, ..., An] または (A1, A2, ..., An)
            if re.match(r'[\[\(].*[\]\)]', token):
                self.parse_array(token)
            # グリッド形式 S1...Sn または Grid[H][W]
            elif 'Grid' in token or re.match(r'S\d+', token):
                self.parse_grid(token)
            # 単一変数
            else:
                self.parse_single(token)

    def parse_single(self, token):
        """単一変数の解析"""
        # 既に定義済みの変数（N, M, K等）への参照かチェック
        if token in self.variables:
            return

        # 変数名を抽出（数字を除去）
        var_name = re.sub(r'\d+', '', token).lower()

        # 型を推定
        if var_name in ['n', 'm', 'k', 'h', 'w', 'q', 't']:
            var_type = 'int'
        elif var_name in ['x', 'y', 'l', 'r']:
            var_type = 'll'
        elif var_name == 's':
            var_type = 'string'
        else:
            var_type = 'int'  # デフォルト

        self.variables[var_name] = var_type
        self.declarations.append(f"    {var_type} {var_name};")
        self.input_code.append(f"    cin >> {var_name};")

    def parse_array(self, token):
        """配列形式の解析"""
        # [A1, A2, ..., An] -> 配列A、サイズn
        match = re.match(r'[\[\(]([A-Za-z])(\d+).*?([A-Za-z])(\w+)[\]\)]', token)
        if match:
            array_name = match.group(1).lower()
            size_var = match.group(3).lower()

            # サイズ変数が未定義なら追加
            if size_var not in self.variables:
                self.variables[size_var] = 'int'
                self.declarations.append(f"    int {size_var};")
                self.input_code.append(f"    cin >> {size_var};")

            # 配列の宣言と入力
            if array_name in ['a', 'b', 'c', 'v']:
                array_type = 'vi'  # vector<int>
            elif array_name in ['x', 'y']:
                array_type = 'vll'  # vector<ll>
            else:
                array_type = 'vi'

            self.declarations.append(f"    {array_type} {array_name}({size_var});")
            self.input_code.append(f"    cin >> {array_name};")

    def parse_grid(self, token):
        """グリッド形式の解析"""
        if 'Grid' in token:
            # Grid[H][W] 形式
            match = re.match(r'Grid\[([A-Za-z])\]\[([A-Za-z])\]', token)
            if match:
                h_var = match.group(1).lower()
                w_var = match.group(2).lower()

                # H, Wが未定義なら追加
                for var in [h_var, w_var]:
                    if var not in self.variables:
                        self.variables[var] = 'int'
                        self.declarations.append(f"    int {var};")
                        self.input_code.append(f"    cin >> {var};")

                # グリッドの宣言と入力
                self.declarations.append(f"    vs grid({h_var});")
                self.input_code.append(f"    rep(i, {h_var}) cin >> grid[i];")
        else:
            # S1...Sn 形式
            self.declarations.append(f"    vs s;")
            self.input_code.append(f"    // TODO: グリッド入力を実装")

    def generate_template(self, filename="solution.cc"):
        """テンプレートを生成"""
        with open(os.path.join(os.path.dirname(__file__), 'lib2/template.cc'), 'r') as f:
            template = f.read()

        # solve関数内の処理を生成
        solve_content = []

        # 宣言部
        if self.declarations:
            solve_content.extend(self.declarations)
            solve_content.append("")

        # 入力部
        if self.input_code:
            solve_content.append("    // 入力")
            solve_content.extend(self.input_code)
            solve_content.append("")

        # 処理部のプレースホルダー
        solve_content.append("    // TODO: 問題を解く処理を実装")
        solve_content.append("")
        solve_content.append("    // 出力")
        solve_content.append("    ")

        # solve関数を置換
        solve_body = '\n'.join(solve_content)

        # 元のsolve関数を探して置換
        import re
        pattern = r'void solve\(\) \{.*?\n\}'
        replacement = f'void solve() {{\n{solve_body}\n}}'

        # より安全な置換（solve関数の中身だけを置換）
        lines = template.split('\n')
        result_lines = []
        in_solve = False
        solve_found = False

        for i, line in enumerate(lines):
            if 'void solve()' in line:
                in_solve = True
                solve_found = True
                result_lines.append(line)
                # 新しいsolve関数の中身を挿入
                result_lines.extend(solve_content)
                continue

            if in_solve:
                if line.strip() == '}':
                    in_solve = False
                    result_lines.append(line)
                    continue
                else:
                    # 元のsolve関数の中身はスキップ
                    continue

            result_lines.append(line)

        final_template = '\n'.join(result_lines)

        # ファイルに書き込み
        with open(filename, 'w') as f:
            f.write(final_template)

        print(f"✅ テンプレートを生成しました: {filename}")
        return filename

def interactive_mode():
    """インタラクティブモード"""
    print("=" * 50)
    print("競技プログラミング テンプレート生成ツール")
    print("=" * 50)
    print()

    # ファイル名を取得
    filename = input("ファイル名を入力 (デフォルト: solution.cc): ").strip()
    if not filename:
        filename = "solution.cc"
    if not filename.endswith('.cc'):
        filename += '.cc'

    print()
    print("入力形式を入力してください")
    print("例1: N K")
    print("例2: N")
    print("    [A1, A2, ..., An]")
    print("例3: H W")
    print("    Grid[H][W]")
    print()
    print("入力を終了するには空行を入力してください")
    print("-" * 30)

    format_lines = []
    while True:
        line = input()
        if not line:
            break
        format_lines.append(line)

    if not format_lines:
        print("❌ 入力形式が指定されていません")
        return

    # テンプレート生成
    generator = TemplateGenerator()
    generator.parse_format('\n'.join(format_lines))
    generator.generate_template(filename)

    print()
    print("生成された入力処理:")
    print("-" * 30)
    for line in generator.declarations:
        print(line)
    if generator.declarations:
        print()
    for line in generator.input_code:
        print(line)

def main():
    """メイン関数"""
    if len(sys.argv) > 1:
        # コマンドライン引数モード
        if sys.argv[1] == '--help' or sys.argv[1] == '-h':
            print("使い方:")
            print("  python generate.py              # インタラクティブモード")
            print("  python generate.py <file> <fmt> # 直接指定")
            print()
            print("例:")
            print('  python generate.py abc.cc "N K [A1, A2, ..., An]"')
            return

        if len(sys.argv) >= 3:
            filename = sys.argv[1]
            format_str = ' '.join(sys.argv[2:])

            generator = TemplateGenerator()
            generator.parse_format(format_str)
            generator.generate_template(filename)
    else:
        # インタラクティブモード
        interactive_mode()

if __name__ == "__main__":
    main()