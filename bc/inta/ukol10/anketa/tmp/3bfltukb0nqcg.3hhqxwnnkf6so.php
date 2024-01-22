<!DOCTYPE html>
<html lang="cs">
	<head>
		<meta charset="utf-8">
		<title><?= ($subtitle) ?> | anketa</title>
	    <script src="https://code.jquery.com/jquery-3.3.1.min.js"
            integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8="
            crossorigin="anonymous">
		</script>
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css" integrity="sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp" crossorigin="anonymous">
		<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>

	
	</head>
	<body>
	<div style="margin-top:70px"></div>
	<?php if ($SESSION['error']): ?>
		<div class="alert alert-danger" role="alert">
		<span class="glyphicon glyphicon-exclamation-sign" aria-hidden="true"></span>
		<span class="sr-only">Chyba:</span>
		<?= ($SESSION['error'])."
" ?>
		</div>
	<?php endif; ?>
	<?php if ($SESSION['ok']): ?>
		<div class="alert alert-success" role="alert">
		<span class="glyphicon glyphicon-ok-circle" aria-hidden="true"></span>
		<span class="sr-only">Úspěch:</span>
		<?= ($SESSION['ok'])."
" ?>
		</div>
	<?php endif; ?>

	<h1><?= ($subtitle) ?></h1>
		<?php echo $this->render($content,NULL,get_defined_vars(),0); ?>

	<?php echo $this->render('menu.html',NULL,get_defined_vars(),0); ?>
	</body>
</html>
