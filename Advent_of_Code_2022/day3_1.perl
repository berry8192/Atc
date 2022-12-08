#!/usr/bin/perl

# 合計点を保存する変数
my $total_points = 0;

while(<>){
  chomp;
  if($_ eq ""){
    last;
  }

  # 入力された文字列を前半と後半に分割
  my $len = length($_);
  my $front = substr($_, 0, $len/2);
  my $back = substr($_, $len/2, $len/2);

  # 前半と後半に出現する文字を保存するハッシュ
  my %char_front;
  my %char_back;

  # 前半と後半の各文字をハッシュに保存
  for(my $i = 0; $i < $len/2; $i++){
    my $char = substr($front, $i, 1);
    $char_front{$char} = 1;
    $char = substr($back, $i, 1);
    $char_back{$char} = 1;
  }

  # 前半と後半に出現する文字を比較し、加点の対象となる文字を抽出
  my $points = 0;
  foreach my $char (keys %char_front){
    if(exists $char_back{$char}){
      # a~zは1~26点、A~Zは27~52点を加算
      if($char =~ /^[a-z]$/){
        $points += ord($char) - 96;
      }
      elsif($char =~ /^[A-Z]$/){
        $points += ord($char) - 64 + 26;
      }
    }
  }
  # print "points: $points\n";

  # 加点した得点を合計点に加算
  $total_points += $points;
}

# 最後に合計点を表示
print "total points: $total_points\n";
