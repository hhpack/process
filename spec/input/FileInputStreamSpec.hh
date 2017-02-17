<?hh //partial

namespace HHPack\Process\Spec;

use HHPack\Process\Input\FileInputStream;

describe(FileInputStream::class, function () {
  beforeEach(function () {
    $this->path = __DIR__ . '/../fixtures/input.txt';
  });
  describe('read()', function () {
    beforeEach(function () {
      $this->input = new FileInputStream($this->path);
    });
    it('read text', function() {
      $input = $this->input->read();
      expect($input)->toBe("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n");
    });
  });
  describe('close()', function () {
    beforeEach(function () {
      $this->input = new FileInputStream($this->path);
    });
    it('close stream', function() {
      expect($this->input->isOpened())->toBeTrue();
      expect($this->input->isClosed())->toBeFalse();

      $this->input->close();

      expect($this->input->isOpened())->toBeFalse();
      expect($this->input->isClosed())->toBeTrue();
    });
  });
});
