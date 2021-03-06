/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process;

final class ProcessResult implements Displayable {

  public function __construct(
    private ProcessStatus $status,
    private OutputResult $output,
  ) {}

  public function exitCode(): int {
    return $this->status->exitCode();
  }

  public function stdout(): Output {
    return $this->output->stdout();
  }

  public function stderr(): Output {
    return $this->output->stderr();
  }

  public function display(): void {
    $this->status->display();
    $this->output->display();
  }

}
