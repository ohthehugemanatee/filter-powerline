#include <linux/bpf.h>
#include <linux/in.h>
#include <linux/if_ether.h>

#define SEC(NAME) __attribute__((section(NAME), used))

#define htons(x) ((__be16)___constant_swab16((x)))

int homeplug_av_drop(struct xdp_md *ctx) {
  void *data = (void *)(long)ctx->data;
  void *data_end = (void *)(long)ctx->data_end;

  struct ethhdr *eth = data;

  if (data + sizeof(*eth) > data_end) {
      return XDP_PASS;
  }

  if (eth->h_proto == htons(0x88e1) || eth->h_proto == htons(0x8912)) {
      return XDP_DROP;
  }
  else {
      return XDP_PASS;
  }
}

char _license[] SEC("license") = "GPL";
