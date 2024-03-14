#include <iostream>
#include <pqxx/pqxx>

int main(int, char *argv[])
{
  // (Normally you'd check for valid command-line arguments.)

  pqxx::connection c{
    "dbname=pg1 user=postgres password=postgres \
      hostaddr=127.0.0.1 port=5432"};
    
  // pqxx::connection c = pqxx::connection(
  //     "username=temp "
  //     "host=db.corral.tacc.utexas.edu "
  //     "password=timelione "
  //     "dbname=temp");

  // try
  // {
  //     pqxx::connection c = pqxx::connection(
  //     "username=temp "
  //     "host=db.corral.tacc.utexas.edu "
  //     "password=timelione "
  //     "dbname=temp");
  // }
  // catch (const std::exception &e)
  // {
  //     std::cerr << e.what() << std::endl;
  // }


  pqxx::work txn{c};

  // For querying just one single value, the transaction has a shorthand method
  // query_value().
  //
  // Use txn.quote() to escape and quote a C++ string for use as an SQL string
  // in a query's text.
  int employee_id = txn.query_value<int>(
    "SELECT key "
    "FROM emps limit 1");

  std::cout << "Employee #" << employee_id << '\n';

  // Update the employee's salary.  Use exec0() to perform a command and check
  // that it produces no result rows.  If the result does contain data, this
  // will throw an exception.
  //
  // The ID is an integer, so we don't need to escape and quote it when using
  // it in our query text.  Just convert it to its PostgreSQL textual
  // representation using to_string().
  // txn.exec0(
  //   "UPDATE EMPLOYEE "
  //   "SET salary = salary + 1 "
  //   "WHERE id = " + pqxx::to_string(employee_id));

  // Make our change definite.
  txn.commit();
}