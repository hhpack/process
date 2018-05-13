<?hh // partial

namespace HHPack\Process\Example;

require_once __DIR__.'/../vendor/autoload.php';

use HHPack\Process as process;
use HHPack\Process\ProcessOptions;
use HHPack\Process\Input\StringInputStream;
use HHPack\Process\Output\{Stdout, Stderr};

async function fork_example(): Awaitable<void> {
  $options = new ProcessOptions();
  $options->stdin(new StringInputStream("abcd\n"));
  $options->stdout(new Stdout());
  $options->stderr(new Stderr());

  using ($p = process\fork(__DIR__.'/scripts/fork_script.hh', ['a', 'b'], $options)) {
    $result = await $p->wait();
    $result->display();
  }
}

fork_example();
