/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process\Descriptor;

use HHPack\Process\Stream\StreamType;

interface DescriptorSpecification<T> {
  public function type(): StreamType;
  public function values(): array<string>;
  public function createStreamFromHandle(resource $handle): T;
}
