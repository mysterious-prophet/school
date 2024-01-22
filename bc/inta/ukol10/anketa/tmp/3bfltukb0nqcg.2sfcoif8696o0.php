
<nav  class="navbar navbar-inverse navbar-fixed-top">
<div class="container-fluid">
    <div class="navbar-header">
      <a class="navbar-brand" href="#">Anketa</a>
    </div>
	<ul class="nav navbar-nav">
<?php if (isset($SESSION['userID'])): ?>
	
		<p class="navbar-text">Uživatel: <?= ($SESSION['name']) ?></p>
		<li><a href="<?= ($BASE) ?>/survey">Nová anketa</a></li>
		<li><a href="<?= ($BASE) ?>/logout">Odhlásit se</a></li>
	
	<?php else: ?>
		<li><a href="<?= ($BASE) ?>/login">Přihlásit se</a></li>
	
<?php endif; ?>
	</ul>
</div>
</nav>