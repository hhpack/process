process
=======================================

[![Latest Stable Version](https://poser.pugx.org/hhpack/process/v/stable)](https://packagist.org/packages/hhpack/process)
[![Build Status](https://travis-ci.org/hhpack/process.svg)](https://travis-ci.org/hhpack/process)
[![Dependency Status](https://www.versioneye.com/user/projects/56298e1036d0ab00160011a2/badge.svg?style=flat)](https://www.versioneye.com/user/projects/56298e1036d0ab00160011a2)
[![License](https://poser.pugx.org/hhpack/process/license)](https://packagist.org/packages/hhpack/process)

Basic usage
----------------------------------------

Start the process, it is an example to wait until the end.  
information of stdout and stderr are output to the buffer.

```hack
use hhpack\process\Process;

async function main() : Awaitable<void>
{
    $result = await Process::exec('hh_client restart');
    $result->getStdout()->display();
    $result->getStderr()->display();

    $result = await Process::exec('hh_client check --json');
    $result->display();
}

main();
```

Run the test
----------------------------------------

You can run the test with the following command.

	composer install
	composer test
