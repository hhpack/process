/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process;

interface Readable {
  public function eof(): bool;
  public function readAsync(int $length = 4096): Awaitable<string>;
}
