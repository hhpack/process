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

use hhpack\process\Writable;
use hhpack\process\Displayable;

final class OutputBufferedStream implements Writable<int>, Displayable
{

    public function __construct(
        private string $output = ''
    )
    {
    }

    public function write(string $output) : int
    {
        $this->output .= $output;
        return strlen($output);
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
