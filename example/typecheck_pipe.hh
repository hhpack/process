<?hh // partial

namespace HHPack\Process\Example;

require_once __DIR__ . '/../vendor/autoload.php';

use HHPack\Process;
use HHPack\Process\ProcessOptions;
use HHPack\Process\Output\{ Stdout, Stderr };

async function pipe_example() : Awaitable<void>
{
    $options = new ProcessOptions();
    $options->stdout(new Stdout());
    $options->stderr(new Stderr());

    using ($p = Process\spawn('hh_client restart', [], $options)) {
        await $p->wait();
    }

    using ($p = Process\spawn('hh_client check --json', [], $options)) {
        await $p->wait();
    }
}

pipe_example();
