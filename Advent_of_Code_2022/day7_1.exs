defmodule Adder do
  @var 1
  def set_var(val) do
    @var=val
  end
  def addint(command) do
    # IO.puts ("call: " <> command)
    command=String.split(command)
    command=List.first(command)

    if command != "$" and command != "dir" do
      command=Integer.parse(command)
      # IO.puts elem(command, 0)
      @var=@var+elem(command, 0)
      elem(command, 0)
      # ans=ans+command
    else
      0
    end
  end
end

Adder.set_var(0)

"./day7.txt" \
|> File.stream! \
|> Stream.map(&String.trim/1) \
# |> Enum.map(fn(c) -> c end) \
|> Enum.map(&Adder.addint/1) \
|> Enum.sum \
|> IO.puts
