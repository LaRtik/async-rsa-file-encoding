#include "rsa.h"

RSA::Keys RSA::calculateRSAKeys() {
  std::vector<largeIntegerType> primes(1034);
  std::ifstream fin("primes.txt");
  for (int i = 0; i < 1033; i++) {
    int temp;
    fin >> temp;
    primes[i] = temp;
  }

  largeIntegerType p = primes[rand() % 1033];
  largeIntegerType q = primes[rand() % 1033];

  largeIntegerType n = p * q;

  largeIntegerType functionE = (p - 1) * (q - 1);

  largeIntegerType e = 1;
  for (largeIntegerType i = functionE - 1; i > 0; --i) {
    if (gcd(i, functionE) == 1 && prime(i)) {
      e = i;
      break;
    }
  }

  largeIntegerType d;
  for (largeIntegerType i = 0;; ++i) {
    if ((largeIntegerType)i * (largeIntegerType)e %
            (largeIntegerType)functionE ==
        1) {
      d = i;
      break;
    }
  }

  RSA::Keys keys{std::pair<largeIntegerType, largeIntegerType>{e, n},
                 std::pair<largeIntegerType, largeIntegerType>{d, n}};
  return keys;
}

largeIntegerType
RSA::cryptData(largeIntegerType data,
               std::pair<largeIntegerType, largeIntegerType> _publicKey) {
  return fastPow(data, _publicKey.first, _publicKey.second);
}

largeIntegerType
RSA::encryptData(largeIntegerType data,
                 std::pair<largeIntegerType, largeIntegerType> _privateKey) {
  return fastPow(data, _privateKey.first, _privateKey.second);
}

bool RSA::cryptMessage(
    std::vector<largeIntegerType> data,
    std::pair<largeIntegerType, largeIntegerType> _publicKey,
    std::string path) {
  std::ofstream fout(path + "/crypted_data", std::ios::out);
  char splitter = '\n';

  for (auto element : data) {
        auto msg = cryptData(element, _publicKey);
        for (const auto &c : std::to_string(msg))
          fout.write(&c, sizeof(c));
        fout.write(&splitter, sizeof(splitter));
  }

  fout.close();
  return true;
}


std::vector <long long> RSA::encr(const std::vector <long long> &data, int l, int r, std::pair<largeIntegerType, largeIntegerType> _private) {
  std::vector<largeIntegerType> result;
  for (int i = l; i <= r; i++)
        result.push_back(encryptData(data[i], _private));
  return result;
}


std::vector<largeIntegerType>
RSA::encryptMessage(std::vector<largeIntegerType> data,
                    std::pair<largeIntegerType, largeIntegerType> _privateKey) {
  clock_t start, end;
  start = clock();
  std::vector<largeIntegerType> encryptedMessage;
<<<<<<< HEAD
  std::vector<std::future<largeIntegerType>> futures;

   for (largeIntegerType element : data) {
      if (futures.size() > 10) {
          for (int i = 0; i < int(futures.size()); i++) {
              auto res = futures[i].get();
              encryptedMessage.push_back(res);
          }
          futures.clear();
      }
      futures.push_back(
          std::async(std::launch::async, &RSA::encryptData, this, element, _privateKey));
=======
  std::vector<std::future<std::vector<largeIntegerType> > > futures;

  int block_size = data.size() / 10;
  for (int i = 0; i < data.size(); i += block_size) {
        int l = i;
        int r = i + block_size - 1;
        if (r >= data.size())
          r = data.size() - 1;
        futures.push_back(
            std::async(std::launch::async, &RSA::encr, this, data, l, r, _privateKey));
>>>>>>> 1eea95bf1f8a0df052a0b9fc2bbfd09f8de70da5
  }



  for (int i = 0; i < int(futures.size()); i++) {
      auto res = futures[i].get();
      for (const auto &el : res) encryptedMessage.push_back(el);
  }

<<<<<<< HEAD
  /*
  for (const auto &d : data) {
        encryptedMessage.push_back(encryptData(d, _privateKey));
  }
*/
=======
  /*for (const auto &d : data) {
        encryptedMessage.push_back(encryptData(d, _privateKey));
  }*/

>>>>>>> 1eea95bf1f8a0df052a0b9fc2bbfd09f8de70da5
  end = clock();
  qDebug() << double(end - start) / CLOCKS_PER_SEC;

  return encryptedMessage;
}

std::vector<largeIntegerType>
RSA::confuseData(std::vector<std::string> data,
                 std::pair<largeIntegerType, largeIntegerType> _anyKey) {
  std::vector<largeIntegerType> confusedData;
  confusedData.reserve(data.size());
  if (data.size() == 0) {
        return confusedData;
  }

  // largeIntegerType startValue = rand() % 10000 + 100;
  // confusedData.push_back(startValue);

  for (int i = 0; i < int(data.size()); ++i) {
        confusedData.push_back(std::stoll(data[i]));
  }
  return confusedData;
}

std::vector<std::string>
RSA::deconfuseData(std::vector<largeIntegerType> confusedData,
                   std::pair<largeIntegerType, largeIntegerType> _anyKey) {
  std::vector<std::string> data;

  for (auto d : confusedData) {
        data.push_back(std::to_string(d));
  }

  return data;
}
