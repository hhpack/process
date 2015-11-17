<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process\input;

use hhpack\process\PipeType;
use hhpack\process\output\BufferedOutput;
use hhpack\process\Writable;

final class ReadablePipe implements ReadableStream
{

    private bool $opened = true;
    private Writable<int> $output;

    public function __construct(
        private PipeType $type,
        private resource $handle
    )
    {
        $this->output = new BufferedOutput();
    }

    public function eof() : bool
    {
        return feof($this->handle);
    }

    public function isOpened() : bool
    {
        return $this->opened;
    }

    public function isClosed() : bool
    {
        return $this->isOpened() === false;
    }

    public function read(int $length) : void
    {
        $chunk = fread($this->handle, $length);
        $this->output->write($chunk);
    }

    public function getOutput() : Writable<int>
    {
        return $this->output;
    }

    public function isStdout() : bool
    {
        return $this->type === PipeType::Stdout;
    }

    public function isStderr() : bool
    {
        return $this->type === PipeType::Stderr;
    }

    public function close() : void
    {
        fclose($this->handle);
        $this->opened = false;
    }

}
