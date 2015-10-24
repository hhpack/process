<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process;

final class BufferedOutput
{

    public function __construct(
        private string $output = ''
    )
    {
    }

    public function append(string $chunk) : void
    {
        $this->output .= $chunk;
    }

    public function __toString() : string
    {
        return $this->output;
    }

}
