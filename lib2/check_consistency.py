#!/usr/bin/env python3
"""
共通構造体の一貫性をチェックするスクリプト
各ライブラリファイルの共通部分がマスターファイルと一致しているか確認
"""

import os
import re
import sys
from pathlib import Path

def extract_common_section(content, start_marker, end_marker):
    """ファイル内容から共通セクションを抽出"""
    pattern = f"{re.escape(start_marker)}(.*?){re.escape(end_marker)}"
    match = re.search(pattern, content, re.DOTALL)
    if match:
        return match.group(1).strip()
    return None

def check_consistency():
    # マーカー定義
    graph_start = "// ========== 共通グラフ構造体 =========="
    graph_end_options = [
        "// ========== ライブラリ本体 ==========",
        "// ========== サンプルコード =========="
    ]

    # マスターファイル
    master_file = "graph_template.cc"

    # チェック対象のファイル
    graph_files = []

    # lib2ディレクトリ内の.ccファイルを検索
    for file in Path(".").glob("*.cc"):
        with open(file, 'r', encoding='utf-8') as f:
            content = f.read()
            if graph_start in content and file.name != master_file:
                graph_files.append(file.name)

    if not os.path.exists(master_file):
        print(f"❌ マスターファイル {master_file} が見つかりません")
        return False

    # マスターファイルから共通部分を抽出
    with open(master_file, 'r', encoding='utf-8') as f:
        master_content = f.read()

    # マスターファイルから共通部分を抽出（複数の終了マーカーを試す）
    master_graph = None
    for end_marker in graph_end_options:
        master_graph = extract_common_section(master_content, graph_start, end_marker)
        if master_graph:
            break

    if not master_graph:
        print(f"❌ {master_file} から共通構造体を抽出できませんでした")
        return False

    print(f"📋 マスターファイル: {master_file}")
    print(f"   共通構造体のサイズ: {len(master_graph)} 文字\n")

    # 各ファイルをチェック
    all_match = True

    if not graph_files:
        print("ℹ️  グラフ構造体を使用しているファイルはありません")
        return True

    print("🔍 グラフ構造体を使用しているファイル:")

    for file in graph_files:
        with open(file, 'r', encoding='utf-8') as f:
            content = f.read()

        # 各ファイルから共通部分を抽出（複数の終了マーカーを試す）
        file_graph = None
        for end_marker in graph_end_options:
            file_graph = extract_common_section(content, graph_start, end_marker)
            if file_graph:
                break

        if not file_graph:
            print(f"   ❌ {file}: 共通構造体セクションが見つかりません")
            all_match = False
        elif file_graph == master_graph:
            print(f"   ✅ {file}: 一致")
        else:
            print(f"   ❌ {file}: 不一致")
            all_match = False

            # 差分の詳細を表示
            master_lines = master_graph.split('\n')
            file_lines = file_graph.split('\n')

            for i, (m_line, f_line) in enumerate(zip(master_lines, file_lines)):
                if m_line != f_line:
                    print(f"      行 {i+1} で差異:")
                    print(f"        マスター: {m_line[:50]}...")
                    print(f"        ファイル: {f_line[:50]}...")
                    break

            if len(master_lines) != len(file_lines):
                print(f"      行数の差異: マスター {len(master_lines)} 行、ファイル {len(file_lines)} 行")

    print()
    if all_match:
        print("✅ すべてのファイルで共通構造体が一致しています")
    else:
        print("⚠️  一部のファイルで共通構造体が一致していません")
        print("   修正方法: graph_template.cc から共通部分をコピーしてください")

    return all_match

def update_files():
    """不一致のファイルを自動更新（オプション）"""
    print("🔧 共通構造体を自動更新しますか？ (y/n): ", end="")
    response = input().strip().lower()

    if response != 'y':
        print("キャンセルしました")
        return

    # ここに自動更新のロジックを追加可能
    print("⚠️  自動更新機能は未実装です。手動でコピーしてください。")

if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    if not check_consistency():
        print()
        # update_files()  # 必要に応じて有効化
        sys.exit(1)

    sys.exit(0)