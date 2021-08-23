-- Query 101
--      Find the cities and item brands where a customer first buys and returns on web, and then buys again from store.
-- Query type: non PKFK joins

define YEAR = random(1998,2000,uniform);
define CATEGORY = sulist(dist(categories,1,1), 3);
define STATE= sulist(dist(fips_county, 3, 1), 5);
define INCOME = range(random(0, 20, uniform), 30);
define BUY_POTENTIAL = dist(buy_potential, 1, 2);
define DISCOUNT = RANGE(RANDOM (0, 100, UNIFORM), 20);
define _LIMIT=100;

[_LIMITA] select [_LIMITB] c_customer_sk, c_first_name, c_last_name, count(*) as cnt
FROM
store_sales,
store_returns,
web_sales,
date_dim d1,
date_dim d2,
item,
customer,
customer_address,
household_demographics
WHERE
ss_ticket_number = sr_ticket_number
AND ss_customer_sk = ws_bill_customer_sk
AND ss_customer_sk = c_customer_sk
AND c_current_addr_sk = ca_address_sk
AND c_current_hdemo_sk = hd_demo_sk
AND ss_item_sk = sr_item_sk
AND sr_item_sk = ws_item_sk
AND i_item_sk = ss_item_sk
AND i_category IN ('[CATEGORY.1]', '[CATEGORY.2]', '[CATEGORY.3]')
AND sr_returned_date_sk = d1.d_date_sk
AND ws_sold_date_sk = d2.d_date_sk
AND d2.d_date between d1.d_date AND (d1.d_date + interval '90 day')
AND ca_state in ('[STATE.1]', '[STATE.2]', '[STATE.3]', '[STATE.4]', '[STATE.5]')
AND d1.d_year = [YEAR]
AND hd_income_band_sk BETWEEN [INCOME.begin] AND [INCOME.end]
AND hd_buy_potential = '[BUY_POTENTIAL]'
AND ss_sales_price / ss_list_price BETWEEN [DISCOUNT.begin] * 0.01 AND [DISCOUNT.end] * 0.01
GROUP BY c_customer_sk, c_first_name, c_last_name
ORDER BY cnt
;
