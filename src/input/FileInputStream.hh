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

final class FileInputStream implements ReadableStream<int>
{

    private resource $handle;

    public function __construct(
        private string $path
    )
    {
        $this->handle = fopen($this->path, 'r');
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

    public function read(int $length = 4096) : string
    {
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

        return $bufferedOutput;
    }

    public function close() : void
    {
        fclose($this->handle);
    }

}
