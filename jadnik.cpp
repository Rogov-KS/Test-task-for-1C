#include <iostream>
#include <vector>
#include <string>
#include <set>


size_t max_input_size = 1e4;

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& arr) {
  int n = arr.size();
  for (size_t i = 0; i < n; ++i) {
    in >> arr[i];
  }
  return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& arr) {
  int n = arr.size();
  for (size_t i = 0; i < n; ++i) {
    os << arr[i] << " ";
  }
  return os;
}

struct Graph {
 public:
  Graph(int n, int m) : am_ver(n), am_edges(m) {
    g.resize(n + 1);
    InputGraph();
  }

    void InfectTown(int cur_v, std::vector<int>& infected_towns) {
        if (is_infected[cur_v] == true) {
            return;
        }
        is_infected[cur_v] = true;

        for (auto u: g[cur_v]) {
            how_much_neighbors_infected[u] += 1;
            how_much_neighbors_not_infected[u] -= 1;
            if (is_infected[u] == false && how_much_neighbors_infected[u] == 2) {
                InfectTown(u, infected_towns);
            }
        }
    }

    std::pair<bool, int> FindBestCandidate() {
        bool is_all_infected = true;
        int cur_best_candiate = 0;
        int cur_best_amount_of_not_infected_neihbors = -1;

        for (int cur_v = min_ver;  cur_v <= am_ver; cur_v += 1) {
            if (is_infected[cur_v] || (g[cur_v].size() == 0)) {
                continue;
            } else {
                is_all_infected = false;
                if (how_much_neighbors_not_infected[cur_v] > cur_best_amount_of_not_infected_neihbors) {
                    cur_best_candiate = cur_v;
                    cur_best_amount_of_not_infected_neihbors = how_much_neighbors_not_infected[cur_v];
                }
            }
        }
        return std::pair(is_all_infected, cur_best_candiate);
    }

    void IterationsOfTakeMostConnectedWithNotInfectedTown(std::vector<int>& infected_towns) {
        while (true) {
            auto [is_all_infected, best_candidate] = FindBestCandidate();
            if (is_all_infected == true) {
                return;
            }
            infected_towns.push_back(best_candidate);
            InfectTown(best_candidate, infected_towns);
        }
    }

  std::vector<int> FindMinAmountOfInfectedTowns() {
    std::vector<int> infected_towns;
    CountNeighbors();
    InfectLeavesAndIsolated(infected_towns);
    IterationsOfTakeMostConnectedWithNotInfectedTown(infected_towns);
    return infected_towns;
  }


  void InfectLeavesAndIsolated(std::vector<int>& infected_towns) {
        for (int cur_v = min_ver;  cur_v <= am_ver; cur_v += 1) {
            if (g[cur_v].size() == 1 || g[cur_v].size() == 0) {
                infected_towns.push_back(cur_v);
                InfectTown(cur_v, infected_towns);
            }
        }
        return;
    }

    void CountNeighbors() {
        for (int cur_v = min_ver;  cur_v <= am_ver; cur_v += 1) {
            how_much_neighbors_not_infected[cur_v] = g[cur_v].size();
            how_much_neighbors_infected[cur_v] = 0;
        }
    }

 private:
    int64_t min_ver = 1e8;
    int64_t am_ver;
    int64_t am_edges;
    std::vector<std::vector<int>> g;
    std::vector<int> how_much_neighbors_infected;
    std::vector<int> how_much_neighbors_not_infected;
    std::vector<bool> is_infected;


    void InputGraph() {
        am_ver = 0;
        int64_t from, to;
        for (size_t i = 0; i < am_edges; ++i) {
            std::cin >> from >> to;
            g[from].push_back(to);
            g[to].push_back(from);
            am_ver = std::max(am_ver, std::max(from, to));
            min_ver = std::min(min_ver, std::min(from, to));
        }
        is_infected.resize(am_ver + 1, false);
        how_much_neighbors_not_infected.resize(am_ver + 1);
        how_much_neighbors_infected.resize(am_ver + 1);
    }
};

int main() {
    int am_edges;
    std::cin >> am_edges;
    Graph my_graph(max_input_size, am_edges);
     
    auto min_infected_towns = my_graph.FindMinAmountOfInfectedTowns();
    std::cout << min_infected_towns.size() << "\n" << min_infected_towns;
    return 0;
}