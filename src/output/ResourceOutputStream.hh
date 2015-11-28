<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process\output;

final class ResourceOutputStream implements WritableStream
{

    public function __construct(
        private resource $handle
    )
    {
        stream_set_blocking($this->handle, 0);
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
        $read = [];
        $write = [ $this->handle ];
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

    public function write(string $output) : int
    {
        return (int) fwrite($this->handle, $output);
    }

    public function close() : void
    {
        fclose($this->handle);
    }

}
