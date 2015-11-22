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

final class NullOutputStream implements Writable<int>
{

    public function write(string $output) : int
    {
        return strlen($output);
    }

}
