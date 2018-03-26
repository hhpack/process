<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process;

final class ProcessStatus implements Displayable {

  private string $command;
  private ?int $pid;
  private bool $running;
  private bool $signaled;
  private bool $stopped;
  private int $exitcode;
  private int $termsig;
  private int $stopsig;

  public function __construct(CapturedProcessStatus $status) {
    $this->command = $status['command'];
    $this->pid = $status['pid'];
    $this->running = $status['running'];
    $this->signaled = $status['signaled'];
    $this->stopped = $status['stopped'];
    $this->exitcode = $status['exitcode'];
    $this->termsig = $status['termsig'];
    $this->stopsig = $status['stopsig'];
  }

  public function pid(): ?int {
    return $this->pid;
  }

  public function isAlive(): bool {
    return $this->running;
  }

  public function exitCode(): int {
    return $this->exitcode;
  }

  public function display(): void {
    fwrite(STDOUT, 'code: '.(string) $this->exitcode.PHP_EOL);
  }

  public static function fromCapturedStatus(
    CapturedProcessStatus $status,
  ): ProcessStatus {
    return new ProcessStatus($status);
  }

  public static function fromResource(resource $process): ProcessStatus {
    $status = proc_get_status($process);
    return new ProcessStatus($status);
  }

  public static function initial(): ProcessStatus {
    return new ProcessStatus(
      shape(
        'command' => '',
        'pid' => null,
        'running' => true,
        'signaled' => false,
        'stopped' => false,
        'exitcode' => -1,
        'termsig' => 0,
        'stopsig' => 0,
      ),
    );
  }

}
