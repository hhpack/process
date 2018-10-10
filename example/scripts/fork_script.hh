<?hh // partial

foreach ($argv as $value) {
  $text = sprintf('argv = %s%s', (string)$value, PHP_EOL);
  fwrite(STDOUT, $text);
}

while (($input = fgets(STDIN)) !== false) {
  if (feof(STDIN) || $input === '') {
    break;
  }
  fwrite(STDOUT, sprintf('input = %s', $input));
}

exit();
