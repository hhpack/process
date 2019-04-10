namespace HHPack\Process\Example;

require_once __DIR__.'/../vendor/hh_autoload.hh';

use HHPack\Process as process;
use HHPack\Process\ProcessOptions;
use HHPack\Process\Input\StringInputStream;
use HHPack\Process\Output\{Stdout, Stderr};

<<__EntryPoint>>
async function fork_example(): Awaitable<noreturn> {
  $options = new ProcessOptions();
  $options->stdin(new StringInputStream("abcd\n"));
  $options->stdout(new Stdout());
  $options->stderr(new Stderr());

  using (
    $p = process\fork(__DIR__.'/scripts/fork_script.hh', ['a', 'b'], $options)
  ) {
    $result = await $p->wait();
    $result->display();
  }

  exit(0);
}
