import os
import csv

def analyze_input_file(filepath):
    """
    入力ファイルを解析してNの値と木の本数を返す
    """
    with open(filepath, 'r') as f:
        lines = f.readlines()
    
    # 最初の行からN, ti, tjを取得
    first_line = lines[0].strip().split()
    N = int(first_line[0])
    ti = int(first_line[1])
    tj = int(first_line[2])
    
    # 迷路部分を読み込んで木の本数をカウント
    tree_count = 0
    for i in range(1, N + 1):
        maze_line = lines[i].strip()
        tree_count += maze_line.count('T')
    
    return N, ti, tj, tree_count

def main():
    input_dir = "external_tools/in/"
    output_file = "data.csv"
    
    # 結果を格納するリスト
    results = []
    
    # 0000.txt から 1999.txt まで処理
    for i in range(2000):
        filename = f"{i:04d}.txt"
        filepath = os.path.join(input_dir, filename)
        
        if os.path.exists(filepath):
            try:
                N, ti, tj, tree_count = analyze_input_file(filepath)
                results.append({
                    'filename': filename,
                    'N': N,
                    'ti': ti,
                    'tj': tj,
                    'tree_count': tree_count
                })
                print(f"処理完了: {filename} (N={N}, 木の本数={tree_count})")
            except Exception as e:
                print(f"エラー: {filename} - {e}")
        else:
            print(f"ファイルが見つかりません: {filepath}")
    
    # CSVファイルに出力
    with open(output_file, 'w', newline='', encoding='utf-8') as csvfile:
        fieldnames = ['filename', 'N', 'ti', 'tj', 'tree_count']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        
        # ヘッダーを書き込み
        writer.writeheader()
        
        # データを書き込み
        for result in results:
            writer.writerow(result)
    
    print(f"\n集計完了: {len(results)}件のファイルを処理しました")
    print(f"結果は {output_file} に保存されました")
    
    # 簡単な統計情報を表示
    if results:
        N_values = [r['N'] for r in results]
        tree_counts = [r['tree_count'] for r in results]
        
        print(f"\nNの値の範囲: {min(N_values)} - {max(N_values)}")
        print(f"木の本数の範囲: {min(tree_counts)} - {max(tree_counts)}")
        print(f"Nの平均値: {sum(N_values) / len(N_values):.2f}")
        print(f"木の本数の平均値: {sum(tree_counts) / len(tree_counts):.2f}")

if __name__ == "__main__":
    main()
