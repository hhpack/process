# process

[![Latest Stable Version](https://poser.pugx.org/hhpack/process/v/stable)](https://packagist.org/packages/hhpack/process)
[![CircleCI](https://circleci.com/gh/hhpack/process/tree/master.svg?style=svg)](https://circleci.com/gh/hhpack/process/tree/master)
[![Dependency Status](https://www.versioneye.com/user/projects/56298e1036d0ab00160011a2/badge.svg?style=flat)](https://www.versioneye.com/user/projects/56298e1036d0ab00160011a2)
[![License](https://poser.pugx.org/hhpack/process/license)](https://packagist.org/packages/hhpack/process)

## Basic usage

Start the process, it is an example to wait until the end.  
information of stdout and stderr are output to the buffer.

```hack
use HHPack\Process;

<<__EntryPoint>>
async function main() : Awaitable<noreturn>
{
  $result = await Process\exec('hh_client restart');
  $result->stdout()->display();
  $result->stderr()->display();

  $result = await Process\exec('hh_client check --json');
  $result->display();

  exit(0);
}
```

## Execution of the script

If you want to run the script, you can run in **execFile** function.

```hack
use HHPack\Process;

<<__EntryPoint>>
async function main() : Awaitable<noreturn>
{
  $result = await Process\execFile('/path/to/example.hh', [ 'a', 'b' ]);
  $result->stdout()->display();
  $result->stderr()->display();

  exit(0);
}
```

## Manual control of the process

You can use the **spawn** function to generate a new child process.  
To wait for the generated child process to finish use the **wait** method.

```hack
use HHPack\Process;
use HHPack\Process\ProcessOptions;

<<__EntryPoint>>
async function pipe_example() : Awaitable<noreturn>
{
  $options = new ProcessOptions();
  $options->stdout(new Stdout());
  $options->stderr(new Stderr());

  using ($p = Process\spawn('hh_client restart', [], $options)) {
    await $p->wait();
  }

  exit(0);
}
```


## Run the test

You can run the test with the following command.

	composer install
	composer test
