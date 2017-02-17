<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process\Output;

use HHPack\Process\Displayable;

final class BufferedOutputStream implements WritableStream, Displayable
{

    private bool $opened = true;

    public function __construct(
        private string $output = ''
    )
    {
    }

    public function isOpened() : bool
    {
        return $this->opened;
    }

    public function isClosed() : bool
    {
        return $this->isOpened() === false;
    }

    public function ready() : bool
    {
        return $this->isOpened();
    }

    public function notReady() : bool
    {
        return $this->ready() === false;
    }

    public function close() : void
    {
        $this->opened = false;
    }

    public function write(string $output) : int
    {
        $this->output .= $output;
        return strlen($output);
    }

    public function clear() : void
    {
        $this->output = '';
    }

    public function display() : void
    {
        fwrite(STDOUT, (string) $this . PHP_EOL);
    }

    public function __toString() : string
    {
        return $this->output;
    }

}
