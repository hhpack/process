<?hh // partial

while (($input = fgets(STDIN)) !== false) {
  if (feof(STDIN) || $input === '') {
    break;
  }
  fwrite(STDOUT, $input);
}

exit();
