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

final class OutputBufferedStream implements Writable<int>
{

    public function __construct(
        private string $output = ''
    )
    {
    }

    public function append(string $output) : int
    {
        return $this->write($output);
    }

    public function write(string $output) : int
    {
        $this->output .= $output;
        return strlen($output);
    }

    public function __toString() : string
    {
        return $this->output;
    }

}
