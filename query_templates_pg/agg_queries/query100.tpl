--  Query 100
--      Find 2 products that are sold together frequently, ordered by how frequently they are sold together.
--  Query type: self-joins, PKFK joins

define YEAR = random(1998,2000,uniform);
define CATEGORY = sulist(dist(categories,1,1), 2);
define MANAGER = range(random(1, 100, uniform), 20);
define MS= dist(marital_status, 1, 1);
define ES= dist(education, 1, 1);
define PRICE = range(random(1, 300, uniform), 5);
define _LIMIT=100;

[_LIMITA] select [_LIMITB] item1.i_item_sk, item2.i_item_sk, count(*) as cnt
FROM item AS item1,
item AS item2,
store_sales AS s1,
store_sales AS s2,
date_dim,
customer,
customer_address,
customer_demographics
WHERE
item1.i_item_sk < item2.i_item_sk
AND s1.ss_ticket_number = s2.ss_ticket_number
AND s1.ss_item_sk = item1.i_item_sk and s2.ss_item_sk = item2.i_item_sk
AND s1.ss_customer_sk = c_customer_sk
and c_current_addr_sk = ca_address_sk
and c_current_cdemo_sk = cd_demo_sk
AND d_year between [YEAR] and [YEAR] + 1
and d_date_sk = s1.ss_sold_date_sk
and item1.i_category in ('[CATEGORY.1]', '[CATEGORY.2]')
and item2.i_manager_id between [MANAGER.begin] and [MANAGER.end]
and cd_marital_status = '[MS]'
and cd_education_status = '[ES]'
and s1.ss_list_price between [PRICE.begin] and [PRICE.end]
and s2.ss_list_price between [PRICE.begin] and [PRICE.end]
GROUP BY item1.i_item_sk, item2.i_item_sk
ORDER BY cnt
;
