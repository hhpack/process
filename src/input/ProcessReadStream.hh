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

use hhpack\process\Writable;
use hhpack\process\output\BufferedOutputStream;
use hhpack\process\stream\StreamType;

final class ProcessReadStream implements ReadableStream<int>
{

    public function __construct(
        private StreamType $type,
        private resource $handle,
        private Writable<int> $output = new BufferedOutputStream()
    )
    {
        stream_set_blocking($this->handle, 0);
    }

    public function eof() : bool
    {
        return feof($this->handle);
    }

    public function isOpened() : bool
    {
        return is_resource($this->handle);
    }

    public function isClosed() : bool
    {
        return $this->isOpened() === false;
    }

    public function ready() : bool
    {
        $read = [ $this->handle ];
        $write = [];
        $expect = null;

        $ng = ($num = stream_select($read, $write, $expect, 0, 200000)) === false;

        if ($ng || $num <= 0) {
            return false;
        }

        return true;
    }

    public function notReady() : bool
    {
        return $this->ready() === false;
    }

    public function read(int $length = 4096) : string
    {
        if ($this->notReady()) {
            return '';
        }

        $bufferedOutput = '';

        while (($chunk = fread($this->handle, 16384)) !== false) {
            if ((string) $chunk === '') {
                break;
            }
            $bufferedOutput .= (string) $chunk;
        }

        if ($this->eof() && strlen($bufferedOutput) <= 0) {
            $this->close();
        }

        $this->output->write($bufferedOutput);

        return $bufferedOutput;
    }

    public function getOutput() : Output
    {
        return $this->output;
    }

    public function isStdout() : bool
    {
        return $this->type === StreamType::Stdout;
    }

    public function isStderr() : bool
    {
        return $this->type === StreamType::Stderr;
    }

    public function close() : void
    {
        fclose($this->handle);
    }

}
