function epsilon_navratova = nase_epsilon(parametr)
cislo = 1;
epsilon_navratova = 0.1*cislo;

while cislo+epsilon_navratova>cislo
    epsilon_navratova = epsilon_navratova/2;
end

epsilon_navratova = epsilon_navratova*2
parametr;

end