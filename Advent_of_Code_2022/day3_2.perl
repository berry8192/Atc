#!/usr/bin/perl

sub reduce {
  my $rtn = "";
  my ($l1, $l2) = @_;
  # for (my $i = 0; $i < @$l1; $i++) {
  #   for (my $j = 0; $j < @$l2; $j++) {
  #     print "$substr($l1, $i, 1)\n";
  #     print "$substr($l2, $j, 1)\n";
  #     if (substr($l1, $i, 1)==substr($l2, $j, 1)){
  #       $rtn.= substr($l2, $j, 1);
  #       last;
  #     }
  #   }
  # }
  foreach $ch1 (split //, $l1){
    foreach $ch2 (split //, $l2){
      # print "$ch1 $ch2\n";
      if ($ch1 eq $ch2){
        $rtn .= $ch1;
      }
    }
  }
  # print "$rtn\n";
  return $rtn;
}

# 初期値として0点を設定
$score = 0;

# 空行が与えられるまで繰り返す
while (my $line1 = <STDIN>) {
  # 行末文字を除去して文字列を取得
  my $line2 = <STDIN>;
  my $line3 = <STDIN>;
  chomp($line1);
  chomp($line2);
  chomp($line3);
  my $line4 = reduce($line1, $line2);
  my $line5 = reduce($line3, $line4);

  # 文字列から1つの文字を探す
  # 共通して現れる1つの文字を取得
  
  my $char = substr($line5, 0, 1);
  # 文字がa~zであれば1~26点を加算
  if ($char =~ /[a-z]/) {
  # print "$char\n";
    $score += ord($char) - ord('a') + 1;
  }
  # 文字がA~Zであれば27~52点を加算
  elsif ($char =~ /[A-Z]/) {
    $score += ord($char) - ord('A') + 27;
  }
}

# 最終的な点数を標準出力
print "$score\n";
